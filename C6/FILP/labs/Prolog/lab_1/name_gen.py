name = [
    'pavel',
    'kirill',
    'alexander',
    'maxim',
    'peter',
    'german',
    'andrew',
    'konstantin'
    ]

surname = [
    'smirnov',
    'ivanov',
    'lebedev',
    'zuev',
    'avdeev',
    'birukov',
    'odintsov',
    'yakushev',
    'lapin',
    'knyazev',
    'agafonov',
    'trofimov',
    'gavrilov',
    'osipov'
]

lastname = [
    'pavlovich',
    'semenovich',
    'vladimirovich',
    'andreevich',
    'maximovich',
    'grigorievich',
    'arkchipovich',
    'samoilovich',
    'bespalovich',
    'voronovich',
    'sharovich',
    'osipovich'
]

universities = [
    'bmstu',
    'lmsu',
    'mipt',
    'mepi',
    'nsu',
    'tsu',
    'sppu',
    'hsu',
    'itmo'
]

from random import choice
from random import randrange

names = []

for i in range(0, 10):
    names.append(choice(name) + ', ' + choice(surname) + ', ' + choice(lastname))

for i in range(0, 10):
    phone = str(randrange(100, 999)) + ')-' + str(randrange(100, 999)) + '-' + str(randrange(10, 99)) + '-' + str(randrange(10, 99))
    print('phone(' + names[i] +\
        ', "8(' + phone + '").')

for i in range(0, 10):
    print('student(' + names[i] + ', ' + choice(universities) + ').')