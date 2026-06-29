from um import count
import pytest


def test_count():
    assert count("um, yeah.. that's really good") == 1


def test_count_wrong():
    assert count("yummy") == 0


def test_count_invalid():
    assert count("ummm") == 0
    assert count("UM..") == 1
