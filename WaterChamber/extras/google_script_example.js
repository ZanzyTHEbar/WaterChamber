var sheet_name = "Water Chamber Data";

dataPoints = {
  id: "",
  timestamp: "",
  max_temp: "",
  num_temp_sensors: "",
  water_level_percentage: "",
  water_level_liters: "",
  humidity: "",
  humidity_temp: "",
  temp_sensors: []
};

function getMultipleRowsData(dataPoints) {
  var data = [];
  for (var i = 0; i < 1; i++) {
    data.push(
      [dataPoints.id,
      dataPoints.timestamp,
      dataPoints.max_temp,
      dataPoints.num_temp_sensors,
      dataPoints.water_level_percentage,
      dataPoints.water_level_liters,
      dataPoints.humidity,
      dataPoints.humidity_temp,
      ...dataPoints.temp_sensors]);
  }
  return data;
}

function doGet(e) {
  //var params = JSON.stringify(e);
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  //var sheet = ss.getSheetByName(sheet_name);
  var sheet = ss.getSheets()[0];
  var lastRow = sheet.getLastRow();

  dataPoints.id = String(e.parameter.id);
  dataPoints.timestamp = String(e.parameter.timestamp);
  dataPoints.max_temp = Number(e.parameter.max_temp);
  dataPoints.num_temp_sensors = Number(e.parameter.num_temp_sensors);
  dataPoints.water_level_percentage = Number(e.parameter.water_level_percentage);
  dataPoints.water_level_liters = Number(e.parameter.water_level_liters);
  dataPoints.humidity = Number(e.parameter.humidity);
  dataPoints.humidity_temp = Number(e.parameter.humidity_temp);

  for (var i = 0; i < e.parameters.temp_sensors.length; i++) {
    dataPoints.temp_sensors[i] = Number(e.parameters.temp_sensors[i]);
  }

  var data = getMultipleRowsData(dataPoints);
  SpreadsheetApp.getActiveSheet().getRange(lastRow + 1, 1, data.length, data[0].length).setValues(data);
  //return HtmlService.createHtmlOutput(params);
}