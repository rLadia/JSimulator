$(document).ready(function() {
  var isPlaying = false;

  var simulationSpeed = 5;

  $('#slowdown, #speedup').mousedown(function() {
    $(this).addClass("down");
  });

  $('#slowdown, #speedup').mouseup(function() {
    $(this).removeClass("down");
  });

  $('#playpause').click(function() {
    $(this).toggleClass("down");
    isPlaying = !isPlaying;
    if(isPlaying) {
      Simulator.play();
    } else {
      Simulator.pause();
    }
  });

  $('#slowdown').click(function() {
    simulationSpeed --;
    Simulator.setSimulationSpeed(simulationSpeed);
  });

  $('#speedup').click(function() {
    simulationSpeed ++;
    Simulator.setSimulationSpeed(simulationSpeed);
  });

  $('#select-demo').click(function() {
    Simulator.selectDemo();
  });

  $('#select-random').click(function() {
    Simulator.selectRandom();
  });
});
