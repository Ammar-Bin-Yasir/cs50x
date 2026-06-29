from numb3rs import validate
import pytest


def test_validate_units():
    assert validate("0.0.0.0") == True
    assert validate("1.2.3.4") == True
    assert validate("9.9.0.2") == True
    assert validate("-1.2.-3.2") == False
    assert validate("4.4.2.1.") == False

def test_validate_range():
    assert validate("255.255.255.255") == True
    assert validate("275.255.100.9") == False
    assert validate("-1.-1.-0.-2") == False
    assert validate("1000.2.199.999") == False

def test_validate_invalid_values():
    assert validate(". . . .") == False
    assert validate("cat") == False
    assert validate("0,0,0,0") == False

def test_validate_1st_byte():
    assert validate("255.500.512.521") == False
