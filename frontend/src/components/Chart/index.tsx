/* eslint-disable @typescript-eslint/no-explicit-any */
import Highcharts from "highcharts";
import HighchartsReact from "highcharts-react-official";
//import Highcharts from "highcharts/highmaps";
import { useState, useRef, useEffect } from "react";
import type HighchartsTypes from "highcharts-react-official";

export default function Chart(props) {
    const [hoverData, setHoverData] = useState("");
    const chartRef = useRef<HighchartsTypes.RefObject>(null);
    const [chartOptions] = useState({
        title: { text: props.title },
        accessibility: {
            enabled: false,
        },
        xAxis: {
            type: "datetime",
            dateTimeLabelFormats: { second: "%H:%M:%S" },
        },
        yAxis: {
            title: { text: props.yAxis },
        },
        credits: { enabled: false },
        series: [
            {
                showInLegend: false,
                data: [],
            },
        ],
        plotOptions: {
            line: {
                animation: false,
                dataLabels: { enabled: true },
            },
            series: {
                color: props.lineColor,
                point: {
                    events: {
                        mouseOver: (e) => {
                            setHoverData(e.target.category);
                        },
                    },
                },
            },
        },
    });

    useEffect(() => {
        const interval = setInterval(() => {
            if (!chartRef || !chartRef.current) {
                return;
            }
            const chart = chartRef.current.chart;
            chart.series[0].addPoint([new Date().getTime(), props.data]);
        }, props.interval);
        return () => clearInterval(interval);
    }, [props.data, props.interval]);

    return (
        <div className="card">
            <HighchartsReact
                highcharts={Highcharts}
                options={chartOptions}
                allowChartUpdate={true}
                immutable={false}
                updateArgs={[true, true, true]}
                containerProps={{ className: "chartContainer" }}
                ref={chartRef}
            />
            <h3>Hovering over {hoverData}</h3>
        </div>
    );
}
