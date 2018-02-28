function reset_markers(newMarkers){
    // bmapContent里的markers存的是json字符串
    var markersArray = JSON.parse(newMarkers);

    var map_marker_set = new Set();
    for(arrayIndex in markersArray){
        var markerObject = markersArray[arrayIndex];
        var gpsdata = markerObject.gps;

        if (!gpsdata && typeof gpsdata != "undefined" && gpsdata != 0)
            continue;
        var point = new BMap.Point(gpsdata.longitude, gpsdata.latitude);
        var label = new BMap.Label(markerObject.name, {offset:new BMap.Size(20,-10)});

        console.log(point);
        console.log(label);

        var map_marker = new BMap.Marker(point);
        map_marker.setLabel(label);
        map_marker_set.add(map_marker);
    }

    window.globalBMap.clearOverlays();

    map_marker_set.forEach(function(marker)
    {
        window.globalBMap.addOverlay(marker);
    });

}
