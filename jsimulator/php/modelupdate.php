<?php
include("swig/simulator.php");
session_start();

if(isset($_POST["initial_condition"])) {
    $_SESSION["MODEL_DATA"] = $_POST["initial_condition"];
    return;
}

if(php_sapi_name() == 'cli') {
    print "\n---DEBUG MODE---\n";
    $time = 7.0;
    $modelData = [[27, 10, 20, 2, 1]];
} else  {
    $time = floatval($_POST["time"]) / 1000.0;
    $modelData = json_decode($_SESSION["MODEL_DATA"], false);
}

$objectList = new objectList();

convertToObjectList($objectList, $modelData);
update($objectList, $time);
convertToModelData($modelData, $objectList);

checkBoundary($modelData);

$_SESSION["MODEL_DATA"] = json_encode($modelData);

$positionData = array();
convertToPositionData($positionData, $objectList);

echo json_encode($positionData);

deleteObjects($objectList);

function checkBoundary(&$modelData)
{
    $maxSpeed = 35;
    foreach($modelData as $key => &$data) {
        // if object is outside of the boundary, moves it to the other side
        if(isOutsideModel($data[1], $data[2])) {
            moveToOppositeBoundary($data[1], $data[2]);
        }
        reduceSpeed($data[3], $data[4]);
    }
}

function update(&$objectList, $time)
{
    $model = new Model();
    $model->Update($objectList, $time);
}

function convertToModelData(&$modelData, $objectList)
{
    $modelData = array();
    for($i = 0; $i < $objectList->size(); $i++) {
        $object = $objectList->get($i);
        $index = getIndex($object);
        $x = $object->position()->x();
        $y = $object->position()->y();
        $dx = $object->velocity()->x();
        $dy = $object->velocity()->y();

        $value = array($index, $x, $y, $dx, $dy);
        array_push($modelData, $value);
    }
}

function convertToPositionData(&$positionData, $objectList)
{
    $positionData = array();
    for($i = 0; $i < $objectList->size(); $i++) {
        $object = $objectList->get($i);
        $index = getIndex($object);
        $x = $object->position()->x();
        $y = $object->position()->y();

        $value = array($index, $x, $y);
        array_push($positionData, $value);
    }
}

function getIndex($modelObject)
{
    $indexedObjectPtr = simulator::ptr_cast_ModelObject_to_IndexedModelObject($modelObject);
    $indexedObject = simulator::IndexedObjectPtr_value($indexedObjectPtr);
    $index = $indexedObject->get_index();
    return $index;
}

function convertToObjectList(&$objectList, $modelData) 
{
    foreach($modelData as $data) {
        $index = $data[0];
        $x = floatval($data[1]);
        $y = floatval($data[2]);
        $dx = floatval($data[3]);
        $dy = floatval($data[4]);

        $object = new IndexedModelObject(
            $index,                         // index
            new Vector3D($x, $y, 0.0),      // center
            new Vector3D($dx, $dy, 0.0),    // velocity
            new Vector3D(0.0, 0.0, 0.0),    // force
            1000.0,                         // mass
            1.0                             // radius
        );
        
        $objectList->push(copy_IndexedObjectPtr($object));
    }
}

function deleteObjects(&$objectList)
{
    while(!$objectList->is_empty()) {
        delete_ModelObjectPtr($objectList->pop());
    }
}

function isOutsideModel($x, $y)
{
    $modelWidth = 1000;
    $modelHeight = 1000;
    return ($x < 0 || $x > $modelWidth 
         || $y < 0 || $y > $modelHeight);
}

function moveToOppositeBoundary(&$x, &$y) 
{
    $modelWidth = 1000;
    $modelHeight = 1000;
    
    if($y > $modelHeight)
        $y -= $modelHeight;
    else if($y < 0)
        $y += $modelHeight;


    if($x > $modelWidth)
        $x -= $modelWidth;
    else if($x < 0)
        $x += $modelWidth;
}

function reduceSpeed(&$dx, &$dy)
{
    $maxSpeed = 50;
    $dragX = 0; // amount to modify speed
    $dragY = 0;
    
    if(abs($dx) > $maxSpeed)
        $dragX = (abs($dx) - $maxSpeed) / 3; 
    
    $dx -= ($dx > 0 ? $dragX : -1 * $dragX);
    
    if(abs($dy) > $maxSpeed)
        $dragY = (abs($dy) - $maxSpeed) / 3; 
        
    $dy -= ($dy > 0 ? $dragY : -1 * $dragY);
}

?>
