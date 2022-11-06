import Header from "@components/Header";
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
            <Header name="Water Chamber" />
            {/* <div className="flex flex-row flex-grow">
                <Sidebar name="Water Chamber"/>
            </div>
            <div className="flex flex-row flex-grow p-10 text-center">
                <button className="bg-blue-700 hover:bg-blue-800 focus:outline-none text-white font-medium text-sm rounded-lg py-2.5 px-5 text-rounded mr-5">
                    Button
                </button>
            </div> */}
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
