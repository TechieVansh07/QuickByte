const express = require("express");
const cors = require("cors");
const { spawn } = require("child_process");

const app = express();

const PORT = 8000;


// Middleware

app.use(cors());

app.use(express.json());


// Start C++ program

const cpp = spawn("./smartfood.exe");


cpp.stdout.on("data", (data) =>
{
    console.log(
        "C++:",
        data.toString()
    );
});


cpp.stderr.on("data", (data) =>
{
    console.error(
        "C++ Error:",
        data.toString()
    );
});




// ================================
// LOGIN
// ================================

app.post("/api/login", (req, res) =>
{
    const username =
        req.body.username;

    const password =
        req.body.password;


    // ADMIN

    if (
        username === "admin" &&
        password === "admin123"
    )
    {
        res.json(
        {
            success: true,

            username: username,

            role: "admin"
        });

        return;
    }


    // USER

    if (
        username === "user" &&
        password === "1234"
    )
    {
        res.json(
        {
            success: true,

            username: username,

            role: "user"
        });

        return;
    }


    // INVALID LOGIN

    res.json(
    {
        success: false,

        message:
            "Invalid username or password!"
    });
});




// Test connection

app.get("/api/test", (req, res) =>
{
    res.json(
    {
        success: true,

        message:
            "Frontend and Backend Connected Successfully!"
    });
});


// ================================
// CART
// ================================


// Add food

app.post("/api/cart/add", (req, res) =>
{
    const foodId =
        req.body.foodId;


    cpp.stdin.write(
        `ADD ${foodId}\n`
    );


    res.json(
    {
        success: true,

        message:
            "Food added to cart!"
    });
});


// Remove food

app.post("/api/cart/remove", (req, res) =>
{
    const foodId =
        req.body.foodId;


    cpp.stdin.write(
        `REMOVE ${foodId}\n`
    );


    res.json(
    {
        success: true,

        message:
            "Item removed from cart!"
    });
});


// Clear cart

app.post("/api/cart/clear", (req, res) =>
{
    cpp.stdin.write(
        "CLEAR\n"
    );


    res.json(
    {
        success: true,

        message:
            "Cart cleared!"
    });
});


// Get cart

app.get("/api/cart", (req, res) =>
{
    let output = "";


    const dataHandler = (data) =>
    {
        output += data.toString();


        if (
            output.includes("TOTAL")
        )
        {
            cpp.stdout.removeListener(
                "data",
                dataHandler
            );


            const lines =
                output
                    .trim()
                    .split("\n");


            const items = [];

            let total = 0;


            for (
                const line of lines
            )
            {
                if (
                    line.startsWith("TOTAL")
                )
                {
                    total =
                        parseInt(
                            line.split(" ")[1]
                        );
                }


                else if (
                    line.includes(" ")
                )
                {
                    const parts =
                        line
                            .trim()
                            .split(" ");


                    if (
                        parts.length === 3
                    )
                    {
                        const foodId =
                            parseInt(
                                parts[0]
                            );


                        const price =
                            parseInt(
                                parts[1]
                            );


                        const quantity =
                            parseInt(
                                parts[2]
                            );


                        let name =
                            "Unknown Food";


                        if (
                            foodId === 101
                        )
                        {
                            name =
                                "Burger";
                        }

                        else if (
                            foodId === 102
                        )
                        {
                            name =
                                "Pizza";
                        }

                        else if (
                            foodId === 103
                        )
                        {
                            name =
                                "Coke";
                        }


                        items.push(
                        {
                            foodId:
                                foodId,

                            name:
                                name,

                            price:
                                price,

                            quantity:
                                quantity
                        });
                    }
                }
            }


            res.json(
            {
                success: true,

                items:
                    items,

                total:
                    total
            });
        }
    };


    cpp.stdout.on(
        "data",
        dataHandler
    );


    cpp.stdin.write(
        "DISPLAY\n"
    );
});


// ================================
// PLACE ORDER
// ================================



app.post("/api/order/place", (req, res) =>
{
    const orderId = Number(req.body.orderId);

    if (!Number.isInteger(orderId) || orderId < 100000 || orderId > 999999)
    {
        return res.status(400).json({
            success: false,
            message: "Invalid order ID."
        });
    }

    let output = "";

    const timeout = setTimeout(() =>
    {
        cpp.stdout.removeListener("data", dataHandler);

        if (!res.headersSent)
        {
            res.status(504).json({
                success: false,
                message: "C++ order confirmation timed out."
            });
        }
    }, 5000);

    const dataHandler = (data) =>
    {
        output += data.toString();

        if (output.includes("ORDER_PLACED "))
        {
            clearTimeout(timeout);
            cpp.stdout.removeListener("data", dataHandler);

            const match = output.match(/ORDER_PLACED\s+(\d+)\s+(\d+)/);

            if (match)
            {
                return res.json({
                    success: true,
                    message: "Order placed successfully!",
                    order: {
                        orderId: Number(match[1]),
                        total: Number(match[2])
                    }
                });
            }
        }

        if (output.includes("Cart is empty!"))
        {
            clearTimeout(timeout);
            cpp.stdout.removeListener("data", dataHandler);

            return res.status(400).json({
                success: false,
                message: "Cart is empty!"
            });
        }
    };

    cpp.stdout.on("data", dataHandler);

    console.log("ORDER REQUEST RECEIVED:", orderId);

    cpp.stdin.write(`ORDER ${orderId}\n`);
});

// ================================
// GET PENDING ORDERS
// ================================



app.get("/api/orders", (req, res) =>
{
    let output = "";

    const timeout = setTimeout(() =>
    {
        cpp.stdout.removeListener("data", dataHandler);

        if (!res.headersSent)
        {
            res.status(504).json({
                success: false,
                message: "Timed out while retrieving orders."
            });
        }
    }, 5000);

    const dataHandler = (data) =>
    {
        output += data.toString();

        if (output.includes("ORDERS_END"))
        {
            clearTimeout(timeout);
            cpp.stdout.removeListener("data", dataHandler);

            const lines = output.trim().split(/\r?\n/);
            const orders = [];

            for (const line of lines)
            {
                const match = line.trim().match(/^ORDER\s+(\d+)\s+(\d+)$/);

                if (match)
                {
                    orders.push({
                        orderId: Number(match[1]),
                        total: Number(match[2]),
                        status: "Pending"
                    });
                }
            }

            return res.json({
                success: true,
                orders: orders
            });
        }
    };

    cpp.stdout.on("data", dataHandler);
    cpp.stdin.write("ORDERS\n");
});



// ================================
// PROCESS NEXT ORDER
// ================================


app.post(
    "/api/orders/process",
    (req, res) =>
{
    let output = "";


    const dataHandler = (data) =>
    {
        output += data.toString();


        if (
            output.includes(
                "PROCESSED"
            )
        )
        {
            cpp.stdout.removeListener(
                "data",
                dataHandler
            );


            const parts =
                output
                    .trim()
                    .split(" ");


            if (
                parts.length >= 3
            )
            {
                const orderId =
                    parseInt(
                        parts[1]
                    );


                const total =
                    parseInt(
                        parts[2]
                    );


                res.json(
                {
                    success: true,

                    message:
                        "Order processed successfully!",

                    order:
                    {
                        orderId:
                            orderId,

                        total:
                            total
                    }
                });


                return;
            }
        }


        if (
            output.includes(
                "No pending orders"
            )
        )
        {
            cpp.stdout.removeListener(
                "data",
                dataHandler
            );


            res.json(
            {
                success: false,

                message:
                    "No pending orders!"
            });
        }
    };


    cpp.stdout.on(
        "data",
        dataHandler
    );


    cpp.stdin.write(
        "PROCESS\n"
    );
});


// ================================
// MENU
// ================================


app.get("/api/menu", (req, res) =>
{
    let output = "";


    const dataHandler = (data) =>
    {
        output += data.toString();


        if (
            output.includes(
                "MENU_END"
            )
        )
        {
            cpp.stdout.removeListener(
                "data",
                dataHandler
            );


            const lines =
                output
                    .trim()
                    .split("\n");


            const menu = [];


            for (
                const line of lines
            )
            {
                if (
                    line === "MENU_START" ||
                    line === "MENU_END"
                )
                {
                    continue;
                }


                const parts =
                    line
                        .trim()
                        .split("|");


                if (
                    parts.length === 3
                )
                {
                    menu.push(
                    {
                        id:
                            parseInt(
                                parts[0]
                            ),

                        name:
                            parts[1],

                        price:
                            parseInt(
                                parts[2]
                            )
                    });
                }
            }


            res.json(
            {
                success: true,

                menu:
                    menu
            });
        }
    };


    cpp.stdout.on(
        "data",
        dataHandler
    );


    cpp.stdin.write(
        "MENU\n"
    );
});



/* ================================
   DIJKSTRA ROUTE API
================================ */

app.get("/api/route", (req, res) => {
    const destination = Number(req.query.destination);

    if (
        !Number.isInteger(destination) ||
        destination < 1 ||
        destination > 5
    ) {
        return res.status(400).json({
            success: false,
            message: "Invalid destination. Use a destination ID from 1 to 5."
        });
    }

    let output = "";
    let routeStarted = false;

    const timeout = setTimeout(() => {
        cpp.stdout.removeListener("data", dataHandler);

        if (!res.headersSent) {
            res.status(504).json({
                success: false,
                message: "Route calculation timed out."
            });
        }
    }, 5000);

    const dataHandler = (data) => {
        output += data.toString();

        if (output.includes("ROUTE_START")) {
            routeStarted = true;
        }

        if (routeStarted && output.includes("ROUTE_END")) {
            clearTimeout(timeout);
            cpp.stdout.removeListener("data", dataHandler);

            const routeSection = output.substring(
                output.indexOf("ROUTE_START"),
                output.indexOf("ROUTE_END") + "ROUTE_END".length
            );

            const distanceMatch = routeSection.match(/DISTANCE\s+(\d+)/);
            const nodes = [];

            const nodeRegex =
                /NODE\s+(\d+)\|([^|\r\n]+)\|([\d.-]+)\|([\d.-]+)/g;

            let match;

            while ((match = nodeRegex.exec(routeSection)) !== null) {
                nodes.push({
                    id: Number(match[1]),
                    name: match[2].trim(),
                    latitude: Number(match[3]),
                    longitude: Number(match[4])
                });
            }

            if (!distanceMatch || nodes.length === 0) {
                return res.status(500).json({
                    success: false,
                    message: "Could not parse the C++ route output."
                });
            }

            return res.json({
                success: true,
                distanceKm: Number(distanceMatch[1]),
                destinationId: destination,
                route: nodes
            });
        }
    };

    cpp.stdout.on("data", dataHandler);
    cpp.stdin.write(`ROUTE ${destination}\n`);
});


// ================================
// START SERVER
// ================================


app.listen(
    PORT,
    () =>
    {
        console.log(
            `Server running at http://localhost:${PORT}`
        );
    }
);