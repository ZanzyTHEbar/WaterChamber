/* eslint-disable @typescript-eslint/no-explicit-any */
import Highcharts from "highcharts";
import HighchartsReact from "highcharts-react-official";
//import Highcharts from "highcharts/highmaps";
import React from "react";

var data = {};

class Chart extends React.Component {
    constructor(props) {
        super(props);
        data = this.props.data;
        this.state = {
            // To avoid unnecessary update keep all options in the state.
            chartOptions: {
                title: { text: this.props.title },
                accessibility: {
                    enabled: false,
                },
                xAxis: {
                    type: 'datetime',
                    dateTimeLabelFormats: { second: '%H:%M:%S' },
                },
                yAxis: {
                    title: { text: this.props.yAxis.title.text },
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
                        color: this.props.line.color,
                        point: {
                            events: {
                                mouseOver: this.setHoverData.bind(this),
                            },
                        },
                    },
                },
            },
            hoverData: null,
        };
    }

    afterChartCreated = (chart) => {
        // Highcharts creates a separate chart instance during export
        if (!chart.options.chart.forExport) {
            this.internalChart = chart;
        }
    }

    componentDidMount() {
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
    }

    setHoverData = (e) => {
        // The chart is not updated because `chartOptions` has not changed.
        this.setState({ hoverData: e.target.category });
    };

    render() {
        const { chartOptions, hoverData } = this.state;
        return (
            <div className="card" >
                <HighchartsReact
                    highcharts={Highcharts}
                    options={chartOptions}
                    allowChartUpdate={true}
                    immutable={false}
                    updateArgs={[true, true, true]}
                    containerProps={{ className: "chartContainer" }}
                    callback={this.afterChartCreated}
                />
                <h3>Hovering over {hoverData}</h3>
            </div>
        );
    }
}

export default Chart;
