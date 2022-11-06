/* eslint-disable @typescript-eslint/no-explicit-any */
import Highcharts from "highcharts";
import HighchartsReact from "highcharts-react-official";
//import Highcharts from "highcharts/highmaps";
import { useState } from "react";

export default function Chart(props) {
    const [hoverData, setHoverData] = useState("");
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

    return (
        <div className="card">
            <HighchartsReact
                highcharts={Highcharts}
                options={chartOptions}
                allowChartUpdate={true}
                immutable={false}
                updateArgs={[true, true, true]}
                containerProps={{ className: "chartContainer" }}
                ref={props.chartRef}
            />
            <h3>Hovering over {hoverData}</h3>
        </div>
    );
}
