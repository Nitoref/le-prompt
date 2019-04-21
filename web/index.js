// eslint-disable-next-line import/no-unresolved
// var elementToDrag = document.getElementById('elementToDrag');
// draggable(elementToDrag);


var left = document.querySelectorAll('.left');
var draggable = new window.Draggable.Sortable(left, {
  draggable: '.drag-item',
  appendTo: '.left',
  classes: {
    body: 'draggable-container--is-dragging',
  },
});

var right = document.querySelectorAll('.right');
var rdraggable = new window.Draggable.Sortable(right, {
  draggable: '.drag-item',
  appendTo: '.right',
  classes: {
    body: 'draggable-container--is-dragging',
  },
});

draggable.on('sortable:sorted', function() {
  console.log('sorted!');
});
rdraggable.on('sortable:sorted', function() {
  console.log('sorted!');
});
draggable.on('drag:start', () => console.log('drag:start'));
draggable.on('drag:move', () => console.log('drag:move'));
draggable.on('drag:stop', () => console.log('drag:stop'));
