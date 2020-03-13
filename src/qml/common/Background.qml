import Felgo 3.0
import QtQuick 2.0

Item {
  width: bg.width
  height: bg.height

  // Game Window has a specific size - overdraw area outside so it's not black
  Rectangle { height: 1000; width: bg.width; y: parent.height; color: "#7E6B5D" }
  Rectangle { height: 1000; width: bg.width; y: -1000;         color: "#83D0F5" }

  MultiResolutionImage {
    id: bg
    source: "../../assets/img/bg.png"
  }

  MultiResolutionImage {
    id: rotor
    source: "../../assets/img/rotor.png"
    x: 178
    y: 318
  }

  MovementAnimation {
    target: rotor
    property: "rotation"
    velocity: 90
    running: true
  }
}
