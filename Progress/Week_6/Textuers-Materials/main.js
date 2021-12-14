function init() {
    var enableFog = false;
    var scene = new THREE.Scene();
    var gui = new dat.GUI();

    if (enableFog) {
        scene.fog = new THREE.FogExp2(0xffffff, 0.05); // Create fog (phủ sương) for scene.
    }

    // Create plane (nền).
    planeMaterial = getMaterial("phong", "rgb(255, 255, 255)");
    var plane = getPlane(planeMaterial, 50);
    plane.rotation.x = Math.PI / 2;

    // Create Sphere Geometry
    var sphereMaterial = getMaterial("phong", "rgb(255, 255, 255)");
    var sphereGeometry = getSphere(2, sphereMaterial);
    sphereGeometry.position.y = sphereGeometry.geometry.parameters.radius;

    // Create Spot Light
    var lightLeft = getSpotLight(1, "rgb(255, 220, 180)");
    lightLeft.position.set(-5, 5, -4);
    var lightRight = getSpotLight(1, "rgb(255, 220, 180)");
    lightRight.position.set(5, 5, -4);

    // Manipulate materials
    var loader = new THREE.TextureLoader();
    planeMaterial.map = loader.load("./assets/textures/Concrete_2.jpeg");
    planeMaterial.bumpMap = loader.load("./assets/textures/Concrete_2.jpeg");
    planeMaterial.Scale = 0.01;

    var maps = ["map", "bumpMap"];
    maps.forEach((mapName) => {
        var textures = planeMaterial[mapName];
        textures.wrapS = THREE.RepeatWrapping;
        textures.wrapT = THREE.RepeatWrapping;
        textures.repeat.set(1.5, 1.5);
    });

    // Add Object to Scene
    scene.add(plane);
    scene.add(sphereGeometry);
    scene.add(lightLeft);
    scene.add(lightRight);

    // dat.gui
    var folder1 = gui.addFolder("Light Left");
    folder1.add(lightLeft, "intensity", 0, 10);
    folder1.add(lightLeft.position, "x", -5, 15);
    folder1.add(lightLeft.position, "y", -5, 15);
    folder1.add(lightLeft.position, "z", -5, 15);

    var folder2 = gui.addFolder("Light Right");
    folder2.add(lightRight, "intensity", 0, 10);
    folder2.add(lightRight.position, "x", -5, 15);
    folder2.add(lightRight.position, "y", -5, 15);
    folder2.add(lightRight.position, "z", -5, 15);

    var folder3 = gui.addFolder("Materials");
    folder3.add(sphereMaterial, "shininess", 0, 1000);
    folder3.add(planeMaterial, "shininess", 0, 1000);

    // Create camera and set position.
    var camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 1, 1000);
    camera.position.set(-15, 7, 10);
    camera.lookAt(new THREE.Vector3(0, 0, 0)); // Vị trí mà camera hướng đến.

    var renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor("rgb(120, 120, 120)"); // Clear color (Xoá phông và đặt màu cho phông)
    renderer.shadowMap.enabled = true; // ShadowMap (Đổ bóng).
    renderer.shadowMap.type = THREE.PCFSoftShadowMap; // Type of shadowMap.
    document.getElementById("webgl").appendChild(renderer.domElement);

    var controls = new THREE.OrbitControls(camera, renderer.domElement);

    update(renderer, scene, camera, controls);

    return scene;
}

function getBox(width, height, depth) {
    var geoBox = new THREE.BoxGeometry(width, height, depth);
    var boxMaterial = new THREE.MeshPhongMaterial({ color: "dodgerblue" });
    var box = new THREE.Mesh(geoBox, boxMaterial);
    box.castShadow = true; // Shadow (đổ bóng).
    return box;
}

function getSphere(size, material) {
    var geometry = new THREE.SphereGeometry(size, 24, 24);
    var sphere = new THREE.Mesh(geometry, material);
    sphere.castShadow = true; // Shadow (đổ bóng).

    return sphere;
}

function getPlane(material, size) {
    var geometry = new THREE.PlaneGeometry(size, size);
    material.side = THREE.DoubleSide;
    var obj = new THREE.Mesh(geometry, material);
    obj.receiveShadow = true;

    return obj;
}

function getPointLight(intensity) {
    var light = new THREE.PointLight(0xffffff, intensity);
    light.castShadow = true;

    return light;
}

function getSpotLight(intensity, color) {
    var light = new THREE.SpotLight(color, intensity);
    light.castShadow = true;

    //Set up shadow properties for the light
    light.shadow.bias = 0.001;
    light.shadow.mapSize.width = 2048;
    light.shadow.mapSize.height = 2048;

    return light;
}

function getDirectionalLight(intensity) {
    var light = new THREE.DirectionalLight(0xffffff, intensity);
    light.castShadow = true;

    light.shadow.camera.left = -10;
    light.shadow.camera.bottom = -10;
    light.shadow.camera.right = 10;
    light.shadow.camera.top = 10;

    return light;
}

function getAmbientLight(intensity) {
    var light = new THREE.AmbientLight("rgb(100, 30, 50)", intensity);
    light.castShadow = true;

    return light;
}

function getBoxGrid(quantity, separationMultiplier) {
    var group = new THREE.Group();

    for (var i = 0; i < quantity; i++) {
        var obj = getBox(1, 1, 1);
        obj.position.x = i * separationMultiplier;
        obj.position.y = obj.geometry.parameters.height / 2;
        group.add(obj);
        for (var j = 1; j < quantity; j++) {
            var obj = getBox(1, 1, 1);
            obj.position.x = i * separationMultiplier;
            obj.position.y = obj.geometry.parameters.height / 2;
            obj.position.z = j * separationMultiplier;
            group.add(obj);
        }
    }

    group.position.x = -((separationMultiplier * (quantity - 1)) / 2);
    group.position.z = -((separationMultiplier * (quantity - 1)) / 2);

    return group;
}

function getMaterial(type, color) {
    var selectedMaterial;
    var materialColor = { color: color === undefined ? "rgb(255, 255, 255)" : color };
    switch (type) {
        case "basic":
            selectedMaterial = new THREE.MeshBasicMaterial(materialColor);
            break;
        case "lambert":
            selectedMaterial = new THREE.MeshLambertMaterial(materialColor);
            break;
        case "phong":
            selectedMaterial = new THREE.MeshPhongMaterial(materialColor);
            break;
        case "standard":
            selectedMaterial = new THREE.MeshStandardMaterial(materialColor);
            break;
        default:
            selectedMaterial = new THREE.MeshBasicMaterial(materialColor);
            break;
    }
    return selectedMaterial;
}

function update(renderer, scene, camera, controls) {
    renderer.render(scene, camera);
    controls.update();

    // Loop to create animation
    requestAnimationFrame(function () {
        update(renderer, scene, camera, controls);
    });
}

var scene = init();
