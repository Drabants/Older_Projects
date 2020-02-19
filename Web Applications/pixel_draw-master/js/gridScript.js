var body = document.getElementById("body");
var block = document.createElement("div");
var containerSize = 720;
var color = "#000";
var rainbowOn = false;


function buildGrid(gridSize){
  //the -2 accounts for the top and bottom margin pixels
  var heightWidth= containerSize/gridSize;
  console.log(heightWidth ,gridSize);
  for(i= 0; i<gridSize; i++){
    for(s=0; s<gridSize; s++){
      $("<div class='block'></div>").appendTo($('#container'));
    }
  }
   $('.block').css({'width': heightWidth, 'height': heightWidth});

}

function resetGrid(){
  var gridSize = prompt("Please input a number between 1 and 100.");
  while(gridSize <1 || gridSize >100 || isNaN(gridSize)){
    if(gridsize === null){
      return;
    }
    gridSize = prompt("Your input is not valid. Please use a number between 1 and 100.");
  }
  $('#container').empty();
  $(".block").css("background-color", "white");
  buildGrid(gridSize);
}

function setBlack(){
  color ="#000";
  rainbowOn = false;
  $('#blackButton').css({'background-color': '#808080' , 'color': '#fff'});
  $('#rainbowButton').css({'background-color': '#fff' , 'color': '#1499cf'});
}

function setRainbow(){
  rainbowOn=true;
  $('#blackButton').css({'background-color': '#fff' , 'color': '#1499cf'});
  $('#rainbowButton').css({'background-color': '#808080' , 'color': '#fff'});
}
function randomColor(){
  return "#"+((1<<24)*Math.random()|0).toString(16);
}
$(document).on('mouseenter','.block', function(){
  if(rainbowOn){
    color = randomColor();
    $(this).css({'background-color':color});
  }else{
    $(this).css("background-color", color);
  }
});
$(document).ready(function(){
  setBlack();
  buildGrid(16);
});
