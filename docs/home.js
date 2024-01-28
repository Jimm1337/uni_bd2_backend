async function renderHome() {
    stopFetch();
    tableContainer.innerHTML = '';
    mapContainer.innerHTML = '';
    treeContainer.innerHTML = '';
    if (datatable) datatable.destroy();

    let title1 = document.createElement('h4');
    title1.classList.add('text-center', 'mt-2', 'fw-normal');
    title1.style.marginBottom = '20px';
    title1.textContent = 'Regions of the Czech Republic';
    mapContainer.appendChild(title1);
    let title2 = document.createElement('h4');
    title2.classList.add('text-center', 'mt-2', 'fw-normal');
    title2.textContent = 'Districts of the Czech Republic';
    treeContainer.appendChild(title2);

    fetch('svg/regions.svg', { signal })
        .then(response => response.text())
        .then(svg => {
            mapContainer.innerHTML += svg;
        });

    fetch('svg/districts.svg', { signal })
        .then(response => response.text())
        .then(svg => {
            treeContainer.innerHTML += svg;
        });

    let table = document.createElement('table');
    let thead = document.createElement('thead');
    let tbody = document.createElement('tbody');

    // Create table header
    let headers = ['Capital', 'Official language', 'Area (km²)', 'Total Population', 'Currency'];
    let tr = document.createElement('tr');
    let th = document.createElement('th');
    th.textContent = 'Czech Republic';
    th.style.textAlign = 'center';
    th.colSpan = headers.length;
    tr.appendChild(th);
    thead.appendChild(tr);

    tr = document.createElement('tr');
    headers.forEach(header => {
        th = document.createElement('th');
        th.textContent = header;
        th.style.textAlign = 'center';
        tr.appendChild(th);
    });
    thead.appendChild(tr);
    table.appendChild(thead);

    tr = document.createElement('tr');
    let td;

    td = document.createElement('td');
    td.textContent = 'Prague';
    tr.appendChild(td);

    td = document.createElement('td');
    td.textContent = 'Czech';
    tr.appendChild(td);

    td = document.createElement('td');
    td.textContent = '78,871';
    td.style.textAlign = 'right';
    tr.appendChild(td);

    td = document.createElement('td');
    td.textContent = '10,524,167';
    td.style.textAlign = 'right';
    tr.appendChild(td);

    td = document.createElement('td');
    td.textContent = 'CZK';
    tr.appendChild(td);

    tbody.appendChild(tr);
    table.appendChild(tbody);

    // Append the table to the table container
    tableContainer.appendChild(table);

    table.id = 'myTable'; table.classList.add('table', 'table-bordered');
    datatable = new DataTable('#myTable', {
        dom: 'tpl'
    });
}

renderHome();