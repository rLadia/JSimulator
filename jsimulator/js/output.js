var nvec = new Module.NVector(5, 5);
console.log(nvec.x());
console.log(nvec.y());

var mo = new Module.ModelObject(nvec, nvec, nvec, 2, 2);
console.log("Mass: " + mo.mass());
console.log("X: " + mo.position().x());
console.log("Y: " + mo.position().y());
mo.delete();

nvec.delete();

console.log("BEGIN TEST");

var p1 = new Module.NVector(0, 0);
var p2 = new Module.NVector(10, 0);
var v = new Module.NVector(0, 0);
var f = new Module.NVector(Math.random() * 100, Math.random() * 100);

bodies = new Module.MOVector();

bodies.push_back(new Module.ModelObject(p1, v, f, 1, 1));
bodies.push_back(new Module.ModelObject(p2, v, f, 1, 1));

obj = bodies.get(0);
console.log("Mass: " + obj.mass());
console.log("position: (" + obj.position().x() + ", " + obj.position().y() + ")");
console.log("velocity: (" + obj.velocity().x() + ", " + obj.velocity().y() + ")");

obj = bodies.get(1);
console.log("Mass: " + obj.mass());
console.log("position: (" + obj.position().x() + ", " + obj.position().y() + ")");
console.log("velocity: (" + obj.velocity().x() + ", " + obj.velocity().y() + ")");

p1.delete();
p2.delete();
v.delete();
f.delete();

var model = new Module.Model();
model.update(bodies, 7.5);
console.log("SIMULATION COMPLETE");

obj = bodies.get(0);
console.log("Mass: " + obj.mass());
console.log("position: (" + obj.position().x() + ", " + obj.position().y() + ")");
console.log("velocity: (" + obj.velocity().x() + ", " + obj.velocity().y() + ")");

obj = bodies.get(1);
console.log("Mass: " + obj.mass());
console.log("position: (" + obj.position().x() + ", " + obj.position().y() + ")");
console.log("velocity: (" + obj.velocity().x() + ", " + obj.velocity().y() + ")");

bodies.delete();
