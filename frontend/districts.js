async function renderDistricts(region) {
    stopFetch();
    tableContainer.innerHTML = '';
    treeContainer.innerHTML = '';
    mapContainer.innerHTML = '';
    if (datatable) datatable.destroy();

    let title1 = document.createElement('h4');
    title1.classList.add('text-center', 'mt-2', 'fw-normal');
    title1.style.marginBottom = '20px';
    title1.textContent = 'Districts of the Czech Republic';
    mapContainer.appendChild(title1);

    let table = document.createElement('table');
    let thead = document.createElement('thead');
    let tbody = document.createElement('tbody');

    if (!region) {
        // Create table header
        let headers = ['District', 'Area (km²)', 'Population', 'Population Density (/km²)', 'Region'];
        let tr = document.createElement('tr');
        headers.forEach(header => {
            let th = document.createElement('th');
            th.textContent = header;
            th.style.textAlign = 'center';
            tr.appendChild(th);
        });
        thead.appendChild(tr);
        table.appendChild(thead);

        fetch('svg/districts.svg', { signal })
            .then(response => response.text())
            .then(svg => {
                mapContainer.innerHTML += svg;
            });
        fetch(`${db}/stats/regions`, { signal })
            .then(response => response.json())
            .then(regions => {
                for (let region in regions.info) {
                    fetch(`${db}/stats/districts/${region}`, { signal })
                        .then(response => response.json())
                        .then(data => {
                            // Create table body
                            for (let district in data.info) {
                                let tr = document.createElement('tr');
                                let td;

                                td = document.createElement('td');
                                td.textContent = district;
                                tr.appendChild(td);

                                td = document.createElement('td');
                                td.textContent = parseInt(data.info[district].area).toLocaleString('en-US');
                                td.style.textAlign = 'right';
                                tr.appendChild(td);

                                td = document.createElement('td');
                                td.textContent = parseInt(data.info[district].totalpopulation).toLocaleString('en-US');
                                td.style.textAlign = 'right';
                                tr.appendChild(td);

                                td = document.createElement('td');
                                td.textContent = Math.round(data.info[district].populationdensity).toLocaleString('en-US');
                                td.style.textAlign = 'right';
                                tr.appendChild(td);

                                td = document.createElement('td');
                                td.textContent = region;
                                tr.appendChild(td);

                                tbody.appendChild(tr);
                            }
                            table.appendChild(tbody);

                            // Append the table to the table container
                            tableContainer.appendChild(table);

                            table.id = 'myTable'; table.classList.add('table', 'table-striped', 'table-bordered');

                            setTimeout(() => {
                                datatable = new DataTable('#myTable', {
                                    dom: 'tpl',
                                    destroy: true
                                });
                            }, 500);
                        });
                }
            });

        let countryList = document.createElement('ul');
        countryList.style.marginTop = '45px';
        let topElement = document.createElement('li');
        let a = document.createElement('a');
        a.textContent = 'Czech Republic';
        a.style.fontSize = '.875rem';
        topElement.appendChild(a);
        let count = 1;
        
        let regionList = document.createElement('ul');
        regionList.style.columnCount = 1;
        await fetch(`${db}/stats/regions`, { signal })
            .then(response => response.json())
            .then(data => {
                for (let region in data.info) {
                    let element = document.createElement('li');
                    let a = document.createElement('a');
                    a.textContent = region;
                    a.style.fontSize = '.875rem';
                    let districtList = document.createElement('ul');
                    fetch(`${db}/stats/districts/${region}`, { signal })
                        .then(response => response.json())
                        .then(data => {
                            for (let district in data.info) {
                                let element = document.createElement('li');
                                let a = document.createElement('a');
                                a.textContent = district;
                                a.id = 'link'; a.href = '#'; a.style.fontSize = '.875rem';
                                a.onclick = () => {
                                    const area = document.getElementById(district);
                                    renderMunicipalities(area);
                                    return false;
                                };
                                a.onmouseover = () => {
                                    const area = document.getElementById(district);
                                    area.style.fill = '#2362a2';
                                };
                                a.onmouseout = () => {
                                    const area = document.getElementById(district);
                                    area.style.fill = '';
                                };
                                element.appendChild(a);
                                districtList.appendChild(element);
                                count++;
                                if (count % 32 == 0) regionList.style.columnCount++;
                            }
                        });
                    element.appendChild(a);
                    element.appendChild(districtList);
                    regionList.appendChild(element);
                    count++;
                }
            });
    
        countryList.appendChild(topElement);
        countryList.appendChild(regionList);
        treeContainer.appendChild(countryList);
        return;
    } 


    let headers = ['District', 'Area (km²)', 'Population', 'Population Density (/km²)'];
    let tr = document.createElement('tr');
    headers.forEach(header => {
        let th = document.createElement('th');
        th.textContent = header;
        th.style.textAlign = 'center';
        tr.appendChild(th);
    });
    thead.appendChild(tr);
    table.appendChild(thead);

    fetch(`${db}/stats/districts/${region.id}`, { signal })
        .then(response => response.json())
        .then(data => {
            fetch('svg/districts.svg', { signal })
                .then(response => response.text())
                .then(svg => {
                    let newMapContainer = document.createElement('div');
                    newMapContainer.innerHTML = svg;
                    title1.textContent = `Districts of the ${region.id} region`;
                    mapContainer.innerHTML = '';
                    mapContainer.appendChild(title1);
                    mapContainer.innerHTML += '<svg onmouseout="hideTooltip()" preserveAspectRatio="xMidYMid meet" viewBox="190 5 1020 620"></svg>';
                    let svgElements = newMapContainer.querySelectorAll('path');
                    svgElements.forEach(path => {
                        if (data.info.hasOwnProperty(path.id)) {
                            mapContainer.querySelector('svg').appendChild(path);
                        }
                    });
                });

            for (let district in data.info) {
                let tr = document.createElement('tr');
                let td;

                td = document.createElement('td');
                td.textContent = district;
                tr.appendChild(td);

                td = document.createElement('td');
                td.textContent = parseInt(data.info[district].area).toLocaleString('en-US');
                td.style.textAlign = 'right';
                tr.appendChild(td);

                td = document.createElement('td');
                td.textContent = parseInt(data.info[district].totalpopulation).toLocaleString('en-US');
                td.style.textAlign = 'right';
                tr.appendChild(td);

                td = document.createElement('td');
                td.textContent = Math.round(data.info[district].populationdensity).toLocaleString('en-US');
                td.style.textAlign = 'right';
                tr.appendChild(td);

                tbody.appendChild(tr);
            }
            table.appendChild(tbody);

            // Append the table to the table container
            tableContainer.appendChild(table);

            table.id = 'myTable'; table.classList.add('table', 'table-striped', 'table-bordered');
            datatable = new DataTable('#myTable', {
                dom: 'tpl'
            });
        });
    
    let countryList = document.createElement('ul');
    countryList.style.marginTop = '45px';
    let topElement = document.createElement('li');
    let a = document.createElement('a');
    a.textContent = 'Czech Republic';
    a.id = 'link'; a.href = '#'; a.style.fontSize = '.875rem';
    a.onclick = () => { renderRegions(); return false; };
    topElement.appendChild(a);
    
    let regionList = document.createElement('ul');
    let element = document.createElement('li');
    a = document.createElement('a');
    a.textContent = region.id;
    a.style.fontSize = '.875rem';
    element.appendChild(a);
    regionList.appendChild(element);

    let districtList = document.createElement('ul');
    await fetch(`${db}/stats/districts/${region.id}`, { signal })
        .then(response => response.json())
        .then(data => {
            for (let district in data.info) {
                let element = document.createElement('li');
                let a = document.createElement('a');
                a.textContent = district;
                a.id = 'link'; a.href = '#'; a.style.fontSize = '.875rem';
                a.onclick = () => {
                    const area = document.getElementById(district);
                    renderMunicipalities(area);
                    return false;
                };
                a.onmouseover = () => {
                    const area = document.getElementById(district);
                    area.style.fill = '#2362a2';
                };
                a.onmouseout = () => {
                    const area = document.getElementById(district);
                    area.style.fill = '';
                };
                element.appendChild(a);
                districtList.appendChild(element);
            }
        });

    regionList.appendChild(districtList);
    countryList.appendChild(topElement);
    countryList.appendChild(regionList);
    treeContainer.appendChild(countryList);
}