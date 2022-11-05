/* eslint-disable no-lone-blocks */
/* eslint-disable @typescript-eslint/no-non-null-assertion */
/* eslint-disable @typescript-eslint/no-explicit-any */
import Chart from "@components/Chart";
import Header from "@components/Header";
import getData from "@src/API/getData";
import * as React from "react";
import type Highcharts from "highcharts-react-official";

/* import styles from "./index.module.scss"; */

const chartData = {};

const url = "http://waterchamber.local/api/v1/builtin/command/json?type=data";

export function Main() {
    const chartRef = React.useRef<Highcharts.RefObject>(null);
    const chartRef2 = React.useRef<Highcharts.RefObject>(null);
    const chartRef3 = React.useRef<Highcharts.RefObject>(null);

    React.useEffect(() => {
        const interval = setInterval(async () => {
            if (!chartRef || !chartRef.current) {
                return;
            }
            const data = await getData(url, false);
            
            const chart = chartRef.current.chart;
            chart.series[0].addPoint([new Date().getTime(), data.humidity_dht]);
        }, 3000);
        return () => clearInterval(interval);
    }, []);

    //! TODO: Make this dynamic by mapping over the data - add all the chart params to the json object

    /*const [sidebarState, setSidebarState] = React.useState(false);
    const onSetSidebarOpen = () => {
        setSidebarState(!sidebarState);
    }; */

    const Main = () => (
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
                <div
                    className="chart-div"
                    style={{
                        overflow: "auto",
                    }}
                >
                    <Chart
                        title="Temperature"
                        yAxis="Temperature (°C)"
                        lineColor="#059e8a"
                        data={[]}
                        chartRef={chartRef}
                    />
                    <Chart
                        title="Humidity"
                        yAxis="Humidity (%)"
                        lineColor="#18009c"
                        data={[]}
                        chartRef={chartRef2}
                    />
                    <Chart
                        title="Humidity Temperature"
                        yAxis="Humidity (°C)"
                        lineColor="#059e8a"
                        data={[]}
                        chartRef={chartRef3}
                    />
                </div>
            </div>
        </div>
    );

    return <Main />;
}
