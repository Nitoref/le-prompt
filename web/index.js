// eslint-disable-next-line import/no-unresolved
// var elementToDrag = document.getElementById('elementToDrag');
// draggable(elementToDrag);


var prompt = document.querySelectorAll('.prompt');
var draggable = new window.Draggable.Sortable(prompt, {
  draggable: '.drag-item',
  appendTo: '.prompt',
  classes: {
    body: 'draggable-container--is-dragging',
  },
});

var rprompt = document.querySelectorAll('.rprompt');
var rdraggable = new window.Draggable.Sortable(rprompt, {
  draggable: '.drag-item',
  appendTo: '.rprompt',
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
