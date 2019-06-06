class Segment {
    constructor(content, fg, bg) {
        let l = 10 * content.length;

        let arrow1 = document.createElementNS("http://www.w3.org/2000/svg", "polygon");
        let points1  = [[0.5, 21.5], [9.5, 11.5], [0.5, 0.5], [9.5+l, 0.5], [18.5+l, 11.5], [9.5+l, 21.5]];
        arrow1.setAttribute("points", points1.join(' '));
        arrow1.setAttribute("class", 'segment-shape--inline');

        let arrow2 = document.createElementNS("http://www.w3.org/2000/svg", "polygon");
        let points2  = [[7.5, 21.5], [7.5, 0.5], [9.5+l, 0.5], [18.5+l, 11.5], [9.5+l, 21.5]];
        arrow2.setAttribute("points", points2.join(' '));
        arrow2.setAttribute("class", 'segment-shape--bound');

        let text = document.createElementNS("http://www.w3.org/2000/svg", "text");
        text.setAttribute("x", "11");
        text.setAttribute("y", "16");
        text.setAttribute("fill", fg);
        text.innerHTML = content;

        let group = document.createElementNS("http://www.w3.org/2000/svg", "g");
        group.appendChild(arrow1);
        group.appendChild(arrow2);
        group.appendChild(text);

        let svg = document.createElementNS("http://www.w3.org/2000/svg", "svg");
        svg.setAttribute("viewBox", [0, 0, 20+l, 22].join(" "));
        svg.appendChild(group);

        let el = document.createElement('li');
        el.setAttribute("class", "segment");
        el.appendChild(svg);
        return el;
    }
}
// 'Salmon' 'LightSalmon' 'NavajoWhite' 'Turquoise' 'AquaMarine' 
let segments = {
    jobs    : new Segment( 'jobs'    , 'palegreen', 'transparent') ,
    user    : new Segment( 'user'    , '#005fd7' , 'transparent') ,
    host    : new Segment( 'host'    , '#005fff' , 'transparent') ,
    context : new Segment( 'context' , '#008700' , 'transparent') ,
    status  : new Segment( 'status'  , '#00875f' , 'transparent') ,
    root    : new Segment( 'root'    , '#008787' , 'transparent') ,
    shell   : new Segment( 'shell'   , '#0087af' , 'transparent') ,
    jobs    : new Segment( 'jobs'    , '#5f87af' , 'transparent') ,
    time    : new Segment( 'time'    , '#8787af' , 'transparent') ,
    perms   : new Segment( 'perms'   , '#8787af' , 'transparent') ,
    dir     : new Segment( 'dir'     , '#af87af' , 'transparent') ,
    git     : new Segment( 'git'     , '#d787af' , 'transparent') ,
    hg      : new Segment( 'hg'      , '#ff5fff' , 'transparent') ,
    ssh     : new Segment( 'ssh'     , '#ff5fd7' , 'transparent') ,
    aws     : new Segment( 'aws'     , '#ff87af' , 'transparent') ,
    load    : new Segment( 'load'    , '#ff8787' , 'transparent') ,
    venv    : new Segment( 'venv'    , '#ff875f' , 'transparent') ,
    docker  : new Segment( 'docker'  , '#ff8700' , 'transparent') ,
}

let left_segments = [
    segments.git,
    segments.dir,
    segments.aws
];
let right_segments = [
    segments.time,
    segments.root,
    segments.jobs,
];

for (let segment in segments) {
    document.getElementById("voidPrompt").appendChild(segments[segment]);
}
for (let segment of left_segments) {
    document.getElementById("leftPrompt").appendChild(segment);
}
for (let segment of right_segments) {
    document.getElementById("rightPrompt").appendChild(segment);
}


// let sortableSegmentList = new Sortable(
//     voidPrompt, {
//         animation: 0,
//         sort: false,
//         group: {
//             name: 'prompt',
//             pull: 'clone',
//             put: 'true'
//         }
//     });


let draggable = new Draggable.Sortable(
    document.querySelectorAll('.prompt, .segment-list'), {
        draggable: 'li'
    }
);

draggable.on('sortable:sorted', (evt) => {
    let mirror = document.querySelector('.draggable-mirror');
    if (evt.newContainer.id == 'rightPrompt') {
        mirror.setAttribute('invert', true);
    } else {
        mirror.setAttribute('invert', false);
    }
});
