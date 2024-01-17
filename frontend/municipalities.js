async function renderMunicipalities(district) {
    stopFetch();
    tableContainer.innerHTML = '';
    treeContainer.innerHTML = '';

    let table = document.createElement('table');
    let thead = document.createElement('thead');
    let tbody = document.createElement('tbody');
    
    if (!district) {
        let title2 = document.createElement('h4');
        title2.classList.add('text-center', 'mt-2', 'fw-normal');
        title2.textContent = 'Municipalities of the Czech Republic';
        tableContainer.appendChild(title2);
        mapContainer.innerHTML = '';

        // Create table header
        let headers = ['Municipality', 'Postal Code', 'District'];
        let tr = document.createElement('tr');
        headers.forEach(header => {
            let th = document.createElement('th');
            th.textContent = header;
            th.style.textAlign = 'center';
            tr.appendChild(th);
        });
        thead.appendChild(tr);
        table.appendChild(thead);

        const loadBtn = document.createElement('button');
        loadBtn.classList.add('btn', 'btn-light');
        loadBtn.textContent = 'Load More';
        const btnDiv = document.createElement('div');
        btnDiv.classList.add('d-grid', 'gap-2', 'col-6', 'mx-auto', 'p-3');
        btnDiv.appendChild(loadBtn);

        const cityList = [];
        await fetch(`${db}/stats/regions`, { signal })
            .then(response => response.json())
            .then(regions => {
                for (let region in regions.info) {
                    fetch(`${db}/stats/districts/${region}`, { signal })
                        .then(response => response.json())
                        .then(districts => {
                            for (let district in districts.info) {
                                fetch(`${db}/stats/municipalities/${district}`, { signal })
                                    .then(response => response.json())
                                    .then(data => {
                                        for (let city in data.info) {
                                            cityList.push([city, data.info[city].postalcode, district]);
                                        }
                                    });
                            }
                        });
                }
            });

        let i = 0;
        loadBtn.addEventListener('click', () => {
            let j = 18;
            while (j > 0 && i < cityList.length) { 
                let tr = document.createElement('tr');
                let td;

                if (i % 2 === 0) {
                    tr.style.backgroundColor = '#ececec';
                }
                i++;

                td = document.createElement('td');
                td.textContent = cityList[i][0];
                tr.appendChild(td);

                td = document.createElement('td');
                td.textContent = cityList[i][1];
                tr.appendChild(td);

                td = document.createElement('td');
                td.textContent = cityList[i][2];
                tr.appendChild(td);

                tbody.appendChild(tr);
                j--;
            }
        });
        table.appendChild(tbody);
        tableContainer.appendChild(table);
        tableContainer.appendChild(btnDiv);

        setTimeout(() => {
            loadBtn.click();
        }, 500);

        return;
    } 

    let title1 = document.querySelector('.mapcontainer h4');
    title1.textContent = `Municipalities of the ${district.id} district`;

    const regionMap = document.getElementById('regions');
    if (regionMap) {
        await fetch('svg/districts.svg', { signal })
            .then(response => response.text())
            .then(svg => {
                mapContainer.innerHTML = '';
                mapContainer.appendChild(title1);
                mapContainer.innerHTML += svg;
            });
    }

    let districtMap = mapContainer.querySelectorAll('path');
    districtMap.forEach(dist => {
        if (dist.id === district.id) {
            dist.style.fill = '#cacaca';
        } else {
            dist.style.fill = '';
        }
    }); 

    let headers = ['Municipality', 'Postal Code'];
    let tr = document.createElement('tr');
    headers.forEach(header => {
        let th = document.createElement('th');
        th.textContent = header;
        th.style.textAlign = 'center';
        tr.appendChild(th);
    });
    thead.appendChild(tr);
    table.appendChild(thead);

    fetch(`${db}/stats/municipalities/${district.id}`, { signal })
        .then(response => response.json())
        .then(data => {
            // Create table body
            let i = 0;
            for (let city in data.info) {
                let tr = document.createElement('tr');
                let td;

                if (i % 2 === 0) {
                    tr.style.backgroundColor = '#ececec';
                }
                i++;

                td = document.createElement('td');
                td.textContent = city;
                tr.appendChild(td);

                td = document.createElement('td');
                td.textContent = data.info[city].postalcode;
                tr.appendChild(td);

                tbody.appendChild(tr);
            }
            table.appendChild(tbody);

            // Append the table to the table container
            tableContainer.appendChild(table);
        });

    let countryList = document.createElement('ul');
    countryList.addEventListener('mouseover', function(event) {
        hideTooltip();
    });
    countryList.style.marginTop = '45px';
    let topElement = document.createElement('li');
    let a = document.createElement('a');
    a.textContent = 'Czech Republic';
    a.id = 'link'; a.href = '#'; a.style.fontSize = '.875rem';
    a.onclick = () => { 
        let svg = document.querySelector('svg');
        let paths = svg.querySelectorAll('path');
        let numberOfPaths = paths.length;
        if (numberOfPaths > 70) renderDistricts();
        else renderRegions();
        return false;
    };
    topElement.appendChild(a);

    await fetch(`${db}/stats/regions`, { signal })
        .then(response => response.json())
        .then(regions => {
            for (let region in regions.info) {
                fetch(`${db}/stats/districts/${region}`, { signal })
                    .then(response => response.json())
                    .then(districts => {
                        for (let dist in districts.info) {
                            if (dist === district.id) {
                                let regionList = document.createElement('ul');
                                let element = document.createElement('li');
                                a = document.createElement('a');
                                a.textContent = region;
                                a.style.fontSize = '.875rem';
                                element.appendChild(a);
                                regionList.appendChild(element);


                                let districtList = document.createElement('ul');
                                fetch(`${db}/stats/districts/${region}`, { signal })
                                    .then(response => response.json())
                                    .then(districts => {
                                        for (let dist in districts.info) {
                                            element = document.createElement('li');
                                            a = document.createElement('a');
                                            a.textContent = dist;
                                            a.style.fontSize = '.875rem';
                                            if (district.id !== dist) {
                                                a.id = 'link'; a.href = '#'; a.style.fontSize = '.875rem';
                                                a.onclick = () => { 
                                                    const area = document.getElementById(dist);
                                                    renderMunicipalities(area); 
                                                    return false; 
                                                };
                                                a.onmouseover = () => {
                                                    const area = document.getElementById(dist);
                                                    area.style.fill = '#2362a2';
                                                };
                                                a.onmouseout = () => {
                                                    const area = document.getElementById(dist);
                                                    area.style.fill = '';
                                                };
                                            }
                                            element.appendChild(a);
                                            districtList.appendChild(element);
                                        }

                                        countryList.appendChild(topElement);
                                        countryList.appendChild(regionList);
                                        regionList.appendChild(districtList);
                                        treeContainer.appendChild(countryList);
                                    });
                            
                            }
                        }
                    });
            }
        });


}