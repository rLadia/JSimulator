(function( Simulator, $, undefined ) {

  var cppSimulator = new Module.Model();
  var modelData; // stores model data for each object
  var items = []; // stores the view data of each object
  var lastUpdatedTime; // time since last update

  var play = false; // used to toggle the running state of the simulation
  var speedMultiplier = 5;
  var maxSpeedMultiplier = 20;

  var modelWidth = 1000;
  var modelHeight = 1000;
  var numItems;

  Simulator.init = function() {
    $.when(
      LadiaWebGL.init("simulator-canvas"),
      initDemoData()
    ).then( function(){
      LadiaWebGL.drawScene(items);
    });
  };

  Simulator.play = function() {
    play = true;
    startUpdateLoop();
  };

  Simulator.pause = function() {
    play = false;
  };

  Simulator.selectDemo = function() {
    modelData.delete();
    initDemoData();
    LadiaWebGL.drawScene(items);
  };

  Simulator.selectRandom = function() {
    modelData.delete();
    initRandomData();
    LadiaWebGL.drawScene(items);
  };

  // changes the speed of the simulation
  // the speed is capped at +- maxSpeedMultiplier
  Simulator.setSimulationSpeed = function(newSpeed) {
    if(newSpeed <= maxSpeedMultiplier && newSpeed >= 1)
      speedMultiplier = newSpeed;
  };

  Simulator.point = function(x, y) {
    this.x = x;
    this.y = y;
    this.time = 0;
  };

  // Holds information about how the item should be drawn
  Simulator.Item = function(index, x, y, r, g, b) {
    this.isDead = false;
    this.index = index;
    this.x = x;
    this.y = y;
    this.z = 0;

    this.r = r;
    this.g = g;
    this.b = b;
    this.tail = []; // array of points
  };

  // adds the current position to the tail array and gets rid of old tail sections
  Simulator.Item.prototype.AddTailPoint = function(time) {
    var len = this.tail.length;
    for (var i = 0; i < len; ++i) {
      this.tail[i].time += time;

      // remove old tails from the array
      if(this.tail[i].time > 2000) {
        this.tail.splice(i, len-i);
        break;
      }
    }
    this.tail.push(new Simulator.point(this.x, this.y));
  };

  Simulator.Item.prototype.RandomizeColors = function () {
    // Give the item a random color
    this.r = Math.random();
    this.g = Math.random();
    this.b = Math.random();
  };

  Simulator.Item.prototype.toString = function() {
    return "Index: " + this.index + "\nx,y,z: " + this.x + ", " + this.y + ", " + this.yz;
  };

  function startUpdateLoop() {
    lastUpdatedTime = new Date().getTime();
    if(play)
      requestAnimFrame(update);
  };

  function initRandomData() {
    var deferred = $.Deferred();
    var mid = Math.floor(numItems / 2);

    modelData = new Module.MOVector(); // stores model data for each object
    items = [];

    numItems = 15;
    for (var i=0; i < numItems; i++) {
      // equally spaced around center
      var x = Math.random() * modelWidth;
      var y = Math.random() * modelHeight;
      var dx = Math.random() * modelWidth / 16 - modelWidth / 32;
      var dy = Math.random() * modelHeight / 16 - modelWidth / 32;

      // create view data
      var screenCoord = toScreenCoords(x, y);
      items.push(new Simulator.Item(i, screenCoord.x, screenCoord.y,
                                    Math.random(), Math.random(), Math.random()));

      addModelObject(i, x, y, dx, dy);
    }

    deferred.resolve();
    return deferred;
  };

  function initDemoData() {
    var deferred = $.Deferred();

    numItems = 7;
    var mid = Math.floor(numItems / 2);

    modelData = new Module.MOVector(); // stores model data for each object
    items = [];

    for (var i=0; i < numItems; i++) {
      // equally spaced around center
      var x = modelWidth / 2 + (mid - i) * (modelWidth / (numItems + 1));
      var y = modelHeight / 2;
      var dx = 0;
      var dy = (i-mid)*6;

      // create view data
      var screenCoord = toScreenCoords(x, y);
      items.push(new Simulator.Item(i, screenCoord.x, screenCoord.y,
                                    Math.random(), Math.random(), Math.random()));

      addModelObject(i, x, y, dx, dy);
    }

    deferred.resolve();
    return deferred;
  };

  function addModelObject(index, x, y, dx, dy) {
    var position = new Module.NVector(x, y);
    var force = new Module.NVector(0, 0);
    var velocity = new Module.NVector(dx, dy);

    modelObject = new Module.ModelObject(
        position, velocity, force,
        1000, // mass
        1,    // radius
        index
    );

    modelData.push_back(modelObject);

    modelObject.delete();
    position.delete();
    velocity.delete();
    force.delete();

  };

  // returns the time since last call
  function timeSinceLastUpdate() {
      var timeNow = new Date().getTime();
      var elapsed = timeNow - lastUpdatedTime;
      lastUpdatedTime = timeNow;
      return elapsed;
  };

  function convertToViewData(modelData) {
    for(var i = 0; i < numItems; ++i) {
      var obj = modelData.get(i);

      if(obj.isDead) {
        items[i].isDead = true;
        obj.delete();
        continue;
      }

      var pos = obj.position;
      var screenCoord = toScreenCoords(pos.x, pos.y);
      pos.delete();

      items[i].x = screenCoord.x;
      items[i].y = screenCoord.y;

      obj.delete();
    }
  };

  function toScreenCoords(x, y) {
    var screenWidth = 17;
    var screenHeight = 17;

    var screenX = (x / modelWidth - 1/2) * screenWidth;
    var screenY = (y / modelWidth - 1/2) * screenWidth;

    return {x: screenX, y: screenY};
  };

  function updateModel(time) {
    var deferred = $.Deferred();
    var len = items.length;
    /*for(var i = 0; i < len; ++i) {
      items[i].AddTailPoint(time);
    }*/

    cppSimulator.update(modelData, time * (speedMultiplier / 1000));
    keepInBounds();

    convertToViewData(modelData);

    deferred.resolve();
    return deferred;
  };

  function keepInBounds() {
    for(var i = 0; i < numItems; ++i) {
      data = modelData.get(i);
      if(data.isDead) {
        data.delete();
        continue;
      }

      var currentPosition = data.position;

      // if object is outside of the boundary, moves it to the other side
      if(isOutsideModel(currentPosition)) {
        var newPosition = moveToOppositeBoundary(currentPosition);
        data.position = newPosition;
        newPosition.delete();
      }

      var currentVelocity = data.velocity;
      var newSpeed = reduceSpeed(currentVelocity);
      data.velocity = newSpeed;
      newSpeed.delete();

      modelData.set(i, data);

      data.delete();
      currentPosition.delete();
      currentVelocity.delete();
    }

  }

  function isOutsideModel(position) {
    var x = position.x;
    var y = position.y;

    return (x < 0 || x > modelWidth
        || y < 0 || y > modelHeight);
  }

  function moveToOppositeBoundary(position) {
    var x = position.x;
    var y = position.y;

    if(y > modelHeight)
      y -= modelHeight;
    else if(y < 0)
      y += modelHeight;

    if(x > modelWidth)
      x -= modelWidth;
    else if(x < 0)
      x += modelWidth;

    return new Module.NVector(x,y);
  }

  function reduceSpeed(velocity) {
    var dx = velocity.x;
    var dy = velocity.y;

    var maxSpeed = 50;
    var dragX = 0; // amount to modify speed
    var dragY = 0;

    if(Math.abs(dx) > maxSpeed)
      dragX = (Math.abs(dx) - maxSpeed) / 3;

    dx -= (dx > 0 ? dragX : -1 * dragX);

    if(Math.abs(dy) > maxSpeed)
      dragY = (Math.abs(dy) - maxSpeed) / 3;

    dy -= (dy > 0 ? dragY : -1 * dragY);

    return new Module.NVector(dx, dy);
  }

  function update() {
    if(play == false) {
      return; // stop the loop
    }

    var time = timeSinceLastUpdate();
    $.when(
      updateModel(time),
      LadiaWebGL.drawScene(items)
    ).then( function(){ // wait for calculations to finish
      setTimeout( function() {
        requestAnimFrame(update); },
        25 // do not update more than once every 25ms
      );

    });
  };

}( window.Simulator = window.Simulator || {}, jQuery ));
