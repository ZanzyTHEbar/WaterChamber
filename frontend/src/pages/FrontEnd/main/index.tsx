/* eslint-disable no-lone-blocks */
/* eslint-disable @typescript-eslint/no-non-null-assertion */
/* eslint-disable @typescript-eslint/no-explicit-any */

import Header from "@components/Header";

import Sidebar from "@components/Sidebar";
import * as React from "react";
/* import styles from "./index.module.scss"; */

export function Main() {
    const Main = () => (
        <div
            className="h-fit flex flex-col"
            style={{
                height: "97vh",
            }}
        >
            <Header />
            <div
                className="flex flex-1"
                style={{
                    paddingBottom: "20px",
                }}
            >
                <Sidebar />
            </div>
        </div>
    );

    return <Main />;
}
