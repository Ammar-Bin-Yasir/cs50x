from working import convert
import pytest

def test_convert_invalid_values():
    with pytest.raises(ValueError):
        convert("12:60 AM to 13:00 PM")



def test_convert_cornercases():
    assert convert("12 AM to 12:59 PM") == "00:00 to 12:59"
    assert convert("1:00 PM to 12 AM") == "13:00 to 00:00"
    assert convert("4:30 AM to 12:59 PM") == "04:30 to 12:59"

def test_convert_edge_cases():
    with pytest.raises(ValueError):
        convert("9AM to 5PM")
    with pytest.raises(ValueError):
        convert("09:00 to 17:00")
    with pytest.raises(ValueError):
        convert("9 AM - 5 PM")
    with pytest.raises(ValueError):
        convert("10:7 AM - 5:1 PM")
