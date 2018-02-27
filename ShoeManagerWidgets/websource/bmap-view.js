function reset_markers(newMarkers){
    // bmapContent里的markers存的是json字符串
    var markers = JSON.parse(newMarkers);

    var map_marker_set = new Set();
    for(var marker in markers){
        var point = new BMap.Point(marker.lan, marker.lon);
        var label = new BMap.Label(marker.name, {offset:new BMap.Size(20,-10)});
        var map_marker = new BMap.Marker(point);	
        map_marker.setLabel(label);
        map_marker_set.add(map_marker);
    }

    window.globalBMap.clearOverlays();

    map_marker_set.forEach(marker)
    {
        window.globalBMap.addOverlay(marker);
    }

}
