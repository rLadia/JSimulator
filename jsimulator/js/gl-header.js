// Heavily influenced by http://learningwebgl.com/blog/
(function( LadiaWebGL, $, undefined ) {

  var gl;
  var shaderProgram;
  var shaders = {"":""};
  var itemTexture;
  var itemVertexPositionBuffer;
  var itemVertexTextureCoordBuffer;
  var zoom = -15;

  LadiaWebGL.init = function(canvasId){
    var deferred = $.Deferred();
    
    var canvas = document.getElementById(canvasId);
    
    initGL(canvas);
    $.when(
      initShaders(),
      initTexture()
    ).then( function() { // wait until shaders and textures are loaded
      initBuffers();
      gl.clearColor(0.0, 0.0, 0.0, 1.0);
      deferred.resolve();
    });
    
    return deferred;
  }

  LadiaWebGL.drawScene = function(itemList) {
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    mat4.perspective(pMatrix, 45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);

    gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
    gl.enable(gl.BLEND);

    mat4.identity(mvMatrix);
    mat4.translate(mvMatrix, mvMatrix, [0.0, 0.0, zoom]);

    for (var i in itemList) {
      if (!itemList[i].isDead)
        itemList[i].draw();
    }
  }

  function initGL(canvas) {
    gl = WebGLUtils.setupWebGL(canvas);
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;
  }

  // id is either shader-vs or shader-fs
  function getShader(gl, id) {
    var shaderType = id.slice(-2);
    var shader;
    
    if (shaderType == "fs") {
      shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if (shaderType == "vs") {
      shader = gl.createShader(gl.VERTEX_SHADER);
    } else {
      return null;
    }

    gl.shaderSource(shader, shaders[id]);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      alert(gl.getShaderInfoLog(shader));
      return null;
    }

    return shader;
  }

  // Read the source for the shader and assign it to shaders
  function loadShaderSrc(shaders, id) {
    return $.get(id + ".glsl", function(data){
      shaders[id] = data;
    });
  }

  function initShaders() {
    var deferred = new $.Deferred(); // defer until shaders have been initialized
    
    $.when(
      loadShaderSrc(shaders, "shader-fs"),
      loadShaderSrc(shaders, "shader-vs")
    ).then( function(){
      var fragmentShader = getShader(gl, "shader-fs");
      var vertexShader = getShader(gl, "shader-vs");

      shaderProgram = gl.createProgram();
      gl.attachShader(shaderProgram, vertexShader);
      gl.attachShader(shaderProgram, fragmentShader);
      gl.linkProgram(shaderProgram);

      if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
        console.log("Could not initialize shaders");
      }

      gl.useProgram(shaderProgram);

      shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
      gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

      shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
      gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);

      shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
      shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
      shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, "uSampler");
      shaderProgram.colorUniform = gl.getUniformLocation(shaderProgram, "uColor");
      deferred.resolve();
    });
    
    return deferred;
  }

  function handleLoadedTexture(texture) {
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texture.image);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);

    gl.bindTexture(gl.TEXTURE_2D, null);
  }

  function initTexture() {
    var deferred = $.Deferred();
    
    itemTexture = gl.createTexture();
    itemTexture.image = new Image();
    itemTexture.image.onload = function () {
      handleLoadedTexture(itemTexture);
      deferred.resolve();
    }
    itemTexture.image.src = "item.gif";
    return deferred;
  }

  var mvMatrix = mat4.create();
  var mvMatrixStack = [];
  var pMatrix = mat4.create();

  function mvPushMatrix() {
    var copy = mat4.create();
    mat4.copy(copy, mvMatrix);
    mvMatrixStack.push(copy);
  }

  function mvPopMatrix() {
    if (mvMatrixStack.length == 0) {
      throw "Invalid popMatrix!";
    }
    mvMatrix = mvMatrixStack.pop();
  }

  function setMatrixUniforms() {
    gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
    gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
  }

  function degToRad(degrees) {
    return degrees * Math.PI / 180;
  }

  function initBuffers() {
    itemVertexPositionBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, itemVertexPositionBuffer);
    
    vertices = [
      -1.0, -1.0,  0.0,
      1.0, -1.0,  0.0,
      -1.0,  1.0,  0.0,
      1.0,  1.0,  0.0
    ];
    
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    itemVertexPositionBuffer.itemSize = 3;
    itemVertexPositionBuffer.numItems = 4;

    itemVertexTextureCoordBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, itemVertexTextureCoordBuffer);
    
    var textureCoords = [
      0.0, 0.0,
      1.0, 0.0,
      0.0, 1.0,
      1.0, 1.0
    ];
    
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
    itemVertexTextureCoordBuffer.itemSize = 2;
    itemVertexTextureCoordBuffer.numItems = 4;
  }

  function drawItem() {
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, itemTexture);
    gl.uniform1i(shaderProgram.samplerUniform, 0);

    gl.bindBuffer(gl.ARRAY_BUFFER, itemVertexTextureCoordBuffer);
    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, itemVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);

    gl.bindBuffer(gl.ARRAY_BUFFER, itemVertexPositionBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, itemVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

    setMatrixUniforms();
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, itemVertexPositionBuffer.numItems);
  }

  Simulator.Item.prototype.draw = function () {
    mvPushMatrix();

    // Move to the item's position
    mat4.translate(mvMatrix, mvMatrix, [this.x, this.y, this.z]);

    // Draw the item in its main color
    gl.uniform3f(shaderProgram.colorUniform, this.r, this.g, this.b);
    drawItem();

    mvPopMatrix();
  };
}( window.LadiaWebGL = window.LadiaWebGL || {}, jQuery ));
