SELECT municipalities.name, postalcode, districts.name as district, regions.name as region 
FROM municipalities
JOIN districts ON districts.ID = municipalities.districtsID
JOIN regions ON regions.ID = districts.regionsID; 

SELECT *
FROM districtsinregion('Plzeň')
ORDER BY name;

SELECT *
FROM municipalitiesindistrict('Prague')
ORDER BY name;

SELECT *
FROM municipalitiesinregion('Plzeň')
ORDER BY name;

SELECT *
FROM regionsstartingwith('P')
ORDER BY name;

SELECT *
FROM districtsstartingwith('P')
ORDER BY name;

SELECT DISTINCT *
FROM municipalitiesstartingwith('P')
ORDER BY name;

SELECT name, area
FROM districtsinregion('Plzeň')
INNER JOIN districts USING (name)
ORDER BY area DESC;
