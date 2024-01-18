// localhost:8000/swagger/ui

const db = 'http://127.0.0.1:8000';
const mapContainer = document.querySelector('.mapcontainer');
const treeContainer = document.querySelector('.treecontainer');
const tableContainer = document.querySelector('.tablecontainer');
const regionsBtn = document.getElementById('regionsBtn');
const districtsBtn = document.getElementById('districtsBtn');
const municipalitiesBtn = document.getElementById('municipalitiesBtn');
let datatable;

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

// Get the input field
let search = document.querySelector('input[type="search"]');

// Listen for focus event
search.addEventListener('click', function() {
    let autocomplete = document.querySelector('#autocomplete');
    autocomplete.parentElement.classList.remove('show');
    autocomplete.classList.remove('show');
});

// Listen for input event
search.addEventListener('input', function() {
    let value = this.value.toLowerCase();
    // Convert the first letter of each word to uppercase
    value = value.replace(/\b\w/g, function(char) { return char.toUpperCase(); });

    // Clear existing suggestions
    let autocomplete = document.querySelector('#autocomplete');
    autocomplete.innerHTML = '';
    autocomplete.parentElement.classList.remove('show');
    autocomplete.classList.remove('show');

    if (!value) return;

    fetch(`${db}/search/region?prefix=` + value)
        .then(response => response.json())
        .then(data => {
            // Check if data.names is not empty
            if (data.names.length > 0) {
                autocomplete.parentElement.classList.add('show');
                autocomplete.classList.add('show');
                // Add new suggestions
                data.names.forEach(item => {
                    let option = document.createElement('a');
                    option.id = item;
                    option.href = '#';
                    option.onclick = () => {
                        renderDistricts(option);
                        return false;
                    };
                    option.classList.add('dropdown-item');
                    option.addEventListener('click', function(event) {
                        event.preventDefault();
                        search.value = '';
                    });

                    let row = document.createElement('div');
                    row.classList.add('row');

                    let left = document.createElement('div');
                    left.style.flex = "1";
                    left.textContent = item;
                    left.style.fontSize = '0.875rem';
                    row.appendChild(left);

                    let right = document.createElement('div');
                    right.classList.add('text-body-secondary', 'text-end');
                    right.style.flex = "1";
                    right.textContent = 'R';
                    right.style.fontSize = '0.875rem';
                    row.appendChild(right);

                    option.appendChild(row);
                    autocomplete.appendChild(option);
                });
            }
        });

    // http://localhost:8000/search/district/Prague?prefix=P
    fetch(`${db}/search/region?prefix=`)
        .then(response => response.json())
        .then(data => {
            data.names.forEach(item => {
                fetch(`${db}/search/district/${item}?prefix=` + value)
                    .then(response => response.json())
                    .then(data => {
                        if (data.names.length > 0) {
                            autocomplete.parentElement.classList.add('show');
                            autocomplete.classList.add('show');
                            // Add new suggestions
                            data.names.forEach(item => {
                                let option = document.createElement('a');
                                option.id = item;
                                option.href = '#';
                                option.onclick = () => {
                                    renderMunicipalities(option);
                                    return false;
                                };
                                option.classList.add('dropdown-item');
                                option.addEventListener('click', function(event) {
                                    event.preventDefault();
                                    search.value = '';
                                });
            
                                let row = document.createElement('div');
                                row.classList.add('row');
            
                                let left = document.createElement('div');
                                left.style.flex = "1";
                                left.textContent = item;
                                left.style.fontSize = '0.875rem';
                                row.appendChild(left);
            
                                let right = document.createElement('div');
                                right.classList.add('text-body-secondary', 'text-end');
                                right.style.flex = "1";
                                right.textContent = 'D';
                                right.style.fontSize = '0.875rem';
                                row.appendChild(right);
            
                                option.appendChild(row);
                                autocomplete.appendChild(option);
                            });
                        }
                    });
            });
        });

});

// Listen for keydown event
search.addEventListener('keydown', function(event) {
    // Check if the Enter key was pressed
    if (event.key === 'Enter') {
        event.preventDefault();
        // Get the first option in the dropdown
        let firstOption = document.querySelector('#autocomplete .dropdown-item');
        // Check if the first option exists
        if (firstOption) {
            // Simulate a click on the first option
            firstOption.click();
        }
        this.blur();
    }
});