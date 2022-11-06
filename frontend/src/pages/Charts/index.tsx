import Chart from "@components/Chart";
import getData from "@src/API/getData";
import { useRef, useEffect } from "react";
import React from "react";
import type Highcharts from "highcharts-react-official";

// TODO: Map over settings json file to create multiple charts with different settings

const url = "http://waterchamber.local/api/v1/builtin/command/json?type=data";

export default function Charts() {
    const chartRef = useRef<Highcharts.RefObject>(null);
    const chartRef2 = useRef<Highcharts.RefObject>(null);
    const chartRef3 = useRef<Highcharts.RefObject>(null);

    useEffect(() => {
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
                        chartRef={chartRef}
                    />
                    <Chart
                        title="Humidity"
                        yAxis="Humidity (%)"
                        lineColor="#18009c"
                        chartRef={chartRef2}
                    />
                    <Chart
                        title="Humidity Temperature"
                        yAxis="Humidity (°C)"
                        lineColor="#059e8a"
                        chartRef={chartRef3}
                    />
                </div>
            </div>
        </div>
    );
}
