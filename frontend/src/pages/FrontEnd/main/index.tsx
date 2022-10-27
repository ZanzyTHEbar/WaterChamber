/* eslint-disable no-lone-blocks */
/* eslint-disable @typescript-eslint/no-non-null-assertion */
/* eslint-disable @typescript-eslint/no-explicit-any */

import Chart from "@components/Chart";
import Header from "@components/Header";
import * as React from "react";
/* import styles from "./index.module.scss"; */
const chartOptions = {
    tempChart: {
        title: "Temperature",
        data_url: "http://water_chamber.local/api/v1/json/command/data",
        yAxis: {
            title: {
                text: "Temperature (°C)",
            },
        },
        line: {
            color: "#059e8a",
        },
    },
    humiChart: {
        title: "Humidity",
        data_url: "http://water_chamber.local/api/v1/json/command/data",
        yAxis: {
            title: {
                text: "Humidity (%)",
            },
        },
        line: {
            color: "#18009c",
        },
    },
    humiTempChart: {
        title: "Humidity Temperature",
        data_url: "http://water_chamber.local/api/v1/json/command/data",
        yAxis: {
            title: {
                text: "Temperature (°C)",
            },
        },
        line: {
            color: "#059e8a",
        },
    },
};

export function Main() {
    const { tempChart, humiChart, humiTempChart } = chartOptions;

    const Main = () => (
        <div
            className="h-fit flex flex-col"
            style={{
                height: "97vh",
            }}
        >
            <Header />
            <div
                className="chartContainer"
                style={{
                    paddingBottom: "20px",
                }}
            >
                <div
                    className="chart-div"
                    style={{
                        overflow: "auto",
                    }}
                >
                    <Chart {...tempChart} />
                    <Chart {...humiChart} />
                    <Chart {...humiTempChart} />
                </div>
            </div>
        </div>
    );

    return <Main />;
}
