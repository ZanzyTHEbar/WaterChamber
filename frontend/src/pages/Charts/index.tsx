import Chart from "@components/Chart";
import { ChartData } from "@components/ChartData";
import getData from "@src/API/getData";
import { useState, useEffect } from "react";

// recursive function to get data from API
// handles nested objects
function fetchFromObject(obj, prop) {
    if (typeof obj === "undefined") {
        return false;
    }
    const _index = prop.indexOf(".");
    if (_index > -1) {
        return fetchFromObject(
            obj[prop.substring(0, _index)],
            prop.substr(_index + 1)
        );
    }

    return obj[prop];
}

export default function Charts() {
    const [chart, setChart] = useState({
        data: {},
    });

    const updateData = () => {
        ChartData.forEach((chart) => {
            getData(chart.ip + chart.endpoint).then((res) => {
                //console.log(res);
                setChart({
                    data: { ...res },
                });
            });
        });
    };

    useEffect(() => {
        const interval = setInterval(() => {
            updateData();
        }, ChartData[0].interval);
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
                                        data={fetchFromObject(
                                            chart.data,
                                            item.chart_id
                                        )}
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
