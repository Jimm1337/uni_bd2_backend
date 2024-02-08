def insert_regions(lines):
    query = "INSERT INTO Regions (Name, Capital) VALUES"
    for line in lines:
        parts = line.split(' | ')
        name = parts[0].strip()
        capital = parts[1].strip()
        query += f"\n('{name}', '{capital}'),"
    query = query[:-1] + ';'
    return query


def insert_districts(lines):
    query = "INSERT INTO Districts (Name, Area, TotalPopulation, RegionsID) VALUES"
    i = 1
    for line in lines:
        if line[0] == '-':
            i += 1
            continue
        parts = line.split(' | ')
        name = parts[0].strip()
        area = parts[1].strip()
        total_population = parts[2].strip()
        query += f"\n('{name}', {area}, {total_population}, {i}),"
    query = query[:-1] + ';'
    return query


def insert_municipalities(lines):
    query = "INSERT INTO Municipalities (Name, PostalCode, DistrictsID) VALUES"
    i = 1
    for line in lines:
        if line[0] == '-':
            i += 1
            continue
        parts = line.split(' | ')
        name = parts[0].strip()
        postal_code = parts[1].strip()
        query += f"\n('{name}', '{postal_code}', {i}),"
    query = query[:-1] + ';'
    return query


def main():
    file = 'municipalities.txt'

    with open(file, 'r', encoding='utf-8') as input_data:
        lines = input_data.readlines()

    # query = insert_regions(lines)
    # query = insert_districts(lines)
    query = insert_municipalities(lines)

    output_file = open('temp.txt', 'w', encoding='utf-8')
    output_file.write(query)


if __name__ == '__main__':
    main()