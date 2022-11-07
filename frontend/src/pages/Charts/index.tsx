import Chart from "@components/Chart";
import { ChartData } from "@components/ChartData";
import getData from "@src/API/getData";
import { useState, useEffect } from "react";

//! TODO: Map over settings json file to create multiple charts with different settings

const url = "http://waterchamber.local/api/v1/builtin/command/json?type=data";

export default function Charts() {
    const [chart, setChart] = useState({
        data: {},
    });

    const updateData = () => {
        getData(url, false).then((data) => {
            setChart({ data: data });
        });
    };

    useEffect(() => {
        const interval = setInterval(() => {
            updateData();
        }, 3000);
        return () => clearInterval(interval);
    }, []);

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
                    <ul className="flow-root space-y-2 items-center content-center justify-center flex-col">
                        <div>
                            {ChartData.map((item, index) => (
                                <li key={index} className={item.cName}>
                                    {item.interval === 0
                                        ? (item.interval = 3000)
                                        : null}
                                    <Chart
                                        title={item.title}
                                        yAxis={item.yAxis}
                                        lineColor={item.lineColor}
                                        data={chart.data}
                                        interval={item.interval}
                                    />
                                </li>
                            ))}
                        </div>
                    </ul>
                </div>
            </div>
        </div>
    );
}
