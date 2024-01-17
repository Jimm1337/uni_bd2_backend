// -DPG_CONNECTION_STRING="host=localhost port=5432 dbname=bd2 user=Supervisor password=Supervisor"
// backend UI -> localhost:8000/swagger/ui

const db = 'http://127.0.0.1:8000';
const mapContainer = document.querySelector('.mapcontainer');
const treeContainer = document.querySelector('.treecontainer');
const tableContainer = document.querySelector('.tablecontainer');
const regionsBtn = document.getElementById('regionsBtn');
const districtsBtn = document.getElementById('districtsBtn');
const municipalitiesBtn = document.getElementById('municipalitiesBtn');

let controller = new AbortController();
let signal = controller.signal;

function stopFetch() {
    controller.abort();
    controller = new AbortController();
    signal = controller.signal;
}

function displayTooltip(element) {
    // Create or get the tooltip element
    let tooltip = document.querySelector('.mytooltip');
    if (!tooltip) {
        tooltip = document.createElement('div');
        tooltip.classList.add('mytooltip');
        document.body.appendChild(tooltip);
    }
    
    // Set the tooltip content and position
    tooltip.textContent = element.id;
    tooltip.style.display = 'block';
    document.addEventListener('mousemove', function(event) {
        tooltip.style.left = event.clientX + 'px';
        tooltip.style.top = event.clientY - 40 + 'px';
    });
}

function hideTooltip(element) {
    let tooltip = document.querySelector('.mytooltip');
    if (!tooltip) return;
    tooltip.style.display = 'none';
}
