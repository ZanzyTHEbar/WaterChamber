/* eslint-disable @typescript-eslint/no-explicit-any */
import Highcharts from "highcharts";
import HighchartsReact from "highcharts-react-official";
//import Highcharts from "highcharts/highmaps";
import { useState } from "react";

export default function Chart(props) {
    //console.log("Chart props", props);

    const [hoverData, setHoverData] = useState("");
    const [chartOptions, setChartOptions] = useState({
        title: { text: props.title },
        accessibility: {
            enabled: false,
        },
        xAxis: {
            type: 'datetime',
            dateTimeLabelFormats: { second: '%H:%M:%S' },
        },
        yAxis: {
            title: { text: props.yAxis },
        },
        credits: { enabled: false },
        series: [{
            showInLegend: false,
            data: [],
        }],
        plotOptions: {
            line: {
                animation: false,
                dataLabels: { enabled: true }
            },
            series: {
                color: props.lineColor,
                point: {
                    events: {
                        mouseOver: (e) => { setHoverData(e.target.category); },
                    },
                },
            },
        },
    });

    const [chartData, setChartData] = useState({
        chartData: props.data,
    });

    /* componentDidMount() {
        this.interval = setInterval(() => this.updateSeries(), 3000);
    }
    
    updateSeries = () => {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", this.props.data_url, true);
        xhttp.onreadystatechange = function () {
            if (xhttp.readyState === 4 && xhttp.status === 200) {
                let json_obj = JSON.parse(xhttp.responseText);
                console.log(json_obj);
                data = json_obj;
            }
            else {
                console.log(xhttp.statusText);
            }
        };
        xhttp.onerror = function () {
            console.log(xhttp.statusText);
        };
        xhttp.send();
        this.internalChart.series[0].addPoint([(new Date()).getTime(), data.humidity_temp_dht]);
    } */

    return (
        <div className="card" >
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
