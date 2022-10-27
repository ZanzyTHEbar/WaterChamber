/* eslint-disable @typescript-eslint/no-explicit-any */

import Highcharts from "highcharts";
import HighchartsReact from "highcharts-react-official";
//import Highcharts from "highcharts/highmaps";
import React from "react";

class Chart extends React.Component {
    constructor(props) {
        super(props);

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
                    //title: { text: 'Temperature (Fahrenheit)' }
                },
                credits: { enabled: false },
                series: [{
                    showInLegend: false,
                    data: []
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

        setInterval(function () {
            const xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState === 4 && this.status === 200) {
                    const x = new Date().getTime(),
                        y = parseFloat(this.responseText);
                    console.log(this.responseText);
                    console.log("Testing");
                    if (this.state.chartOptions.series[0].data.length > 40) {
                        this.state.chartOptions.series[0].addPoint([x, y], true, true, true);
                    } else {
                        this.state.chartOptions.series[0].addPoint([x, y], true, false, true);
                    }
                }
            };
            xhttp.open("GET", "http://water_chamber.local/api/v1/json/command/data", true);
            xhttp.send();
        }, 3000);
    }

    setHoverData = (e) => {
        // The chart is not updated because `chartOptions` has not changed.
        this.setState({ hoverData: e.target.category });
    };

    updateSeries = () => {
        // The chart is updated only with new options.
        const xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState === 4 && this.status === 200) {
                const x = new Date().getTime(),
                    y = parseFloat(this.responseText);
                console.log(this.responseText);
                console.log("Testing");
                if (this.state.chartOptions.series[0].data.length > 40) {
                    this.state.chartOptions.series[0].addPoint([x, y], true, true, true);
                } else {
                    this.state.chartOptions.series[0].addPoint([x, y], true, false, true);
                }
            }
        };
        xhttp.open("GET", "http://water_chamber.local/api/v1/json/command/data", true);
        xhttp.send();
        console.log("Updating");
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
                />
                <h3>Hovering over {hoverData}</h3>
                <button onClick={this.updateSeries.bind(this)}>
                    Update Series
                </button>
            </div>
        );
    }
}

export default Chart;
