import Charts from "@pages/Charts";
import React from "react";

export default function Home() {
    return (
        <div
            className="h-fit flex flex-col"
            style={{
                height: "97vh",
            }}
        >
            <div
                className="chartContainer"
                style={{
                    paddingBottom: "20px",
                }}
            >
                <Charts />
            </div>
        </div>
    );
}
