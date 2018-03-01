function reset_markers(newMarkers){
    
    console.log(newMarkers);
    
    window.globalBMap.clearOverlays();

    // bmapContent里的markers存的是json字符串
    var markersArray = JSON.parse(newMarkers);

    var nameArray = new Array();
    var realGPSArray = new Array();
    var bmapGPSArray = new Array();

    // 提取硬件gps
    for(arrayIndex in markersArray)
    {
        var markerObject = markersArray[arrayIndex];
        var gpsdata = markerObject.gps;

        if (!gpsdata && typeof gpsdata != "undefined" && gpsdata != 0)
            continue;

        var point = new BMap.Point(gpsdata.longitude, gpsdata.latitude);
        nameArray.push(markerObject.name);
        realGPSArray.push(point)
    }

    if(realGPSArray.length === 0)
    {
        return;
    }
     //坐标转换完之后的回调函数
     translateCallback = function (data)
     {

        if(data.status === 0)
        {
        
            for (var i = 0; i < data.points.length; i++) {
                bmapGPSArray.push(data.points[i]);
            }

            if(nameArray.length == bmapGPSArray.length)
            {
                var map_marker_set = new Set();
                for (var i = 0; i <= Array.length; i++)
                {
                    var map_marker = new BMap.Marker(bmapGPSArray[i]);
                    var label = new BMap.Label(nameArray[i], {offset:new BMap.Size(20,-10)});
                    map_marker.setLabel(label);
                    map_marker_set.add(map_marker);
                }
                
                ;

                map_marker_set.forEach(function(marker)
                {
                    window.globalBMap.addOverlay(marker);
                });
            
            }
        }

        else
        {
            console.log(data);
        }

      }

      // 转换成百度gps
      setTimeout(function(){
          var convertor = new BMap.Convertor();
          convertor.translate(realGPSArray, 1, 5, translateCallback)
      }, 1000);

}
