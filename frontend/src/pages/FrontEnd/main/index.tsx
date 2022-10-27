/* eslint-disable no-lone-blocks */
/* eslint-disable @typescript-eslint/no-non-null-assertion */
/* eslint-disable @typescript-eslint/no-explicit-any */

import Header from "@components/Header";

import Sidebar from "@components/Sidebar";
import * as React from "react";
/* import styles from "./index.module.scss"; */

export function Main() {
    const Main = () => (
        <React.Fragment>
            <div className="h-screen flex flex-col">
                <Header />
                <div
                    className="flex flex-1"
                    style={{
                        borderTopLeftRadius: "8px",
                        borderTopRightRadius: "8px",
                    }}
                >
                    <Sidebar />
                </div>
            </div>
        </React.Fragment>
    );

    return (
        <React.Fragment>
            <Main />
        </React.Fragment>
    );
}
