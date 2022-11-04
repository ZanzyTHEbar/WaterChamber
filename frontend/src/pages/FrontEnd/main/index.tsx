/* eslint-disable no-lone-blocks */
/* eslint-disable @typescript-eslint/no-non-null-assertion */
/* eslint-disable @typescript-eslint/no-explicit-any */

import Chart from "@components/Chart";
import Header from "@components/Header";
import Sidebar from "@components/Sidebar";
import * as React from "react";
/* import styles from "./index.module.scss"; */

const chartOptions = {
    tempChart: {
        title: "Temperature",
        data_url:
            "http://waterchamber.local/api/v1/builtin/command/json?type=data",
        yAxis: {
            title: {
                text: "Temperature (°C)",
            },
        },
        line: {
            color: "#059e8a",
        },
        data: {
            id: "",
            timestamp: "",
            max_temp: 0,
            num_temp_sensors: 0,
            water_level_liters: 0,
            water_level_percent: 0,
            humidity_dht: 0,
            humidity_temp_dht: 0,
            temp_sensors: [],
        },
    },
    humiChart: {
        title: "Humidity",
        data_url:
            "http://waterchamber.local/api/v1/builtin/command/json?type=data",
        yAxis: {
            title: {
                text: "Humidity (%)",
            },
        },
        line: {
            color: "#18009c",
        },
        data: {
            id: "",
            timestamp: "",
            max_temp: 0,
            num_temp_sensors: 0,
            water_level_liters: 0,
            water_level_percent: 0,
            humidity_dht: 0,
            humidity_temp_dht: 0,
            temp_sensors: [],
        },
    },
    humiTempChart: {
        title: "Humidity Temperature",
        data_url:
            "http://waterchamber.local/api/v1/builtin/command/json?type=data",
        yAxis: {
            title: {
                text: "Temperature (°C)",
            },
        },
        line: {
            color: "#059e8a",
        },
        data: {
            id: "",
            timestamp: "",
            max_temp: 0,
            num_temp_sensors: 0,
            water_level_liters: 0,
            water_level_percent: 0,
            humidity_dht: 0,
            humidity_temp_dht: 0,
            temp_sensors: [],
        },
    },
};

export function Main() {
    const { tempChart, humiChart, humiTempChart } = chartOptions;
    const [sidebarState, setSidebarState] = React.useState(false);

    const onSetSidebarOpen = () => {
        setSidebarState(!sidebarState);
    };

    const Main = () => (
        <div
            className="h-fit flex flex-col"
            style={{
                height: "97vh",
            }}
        >
            <Header name="Water Chamber" />
            <div className="flex flex-row flex-grow">
                <Sidebar name="Water Chamber"/>
            </div>
            <div className="flex flex-row flex-grow p-10 text-center">
                <button className="bg-blue-700 hover:bg-blue-800 focus:outline-none text-white font-medium text-sm rounded-lg py-2.5 px-5 text-rounded mr-5">
                    Button
                </button>
            </div>
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
