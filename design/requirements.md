# Requirements

This document lays out functional requirements. These are derived from the [FITS
standard, version 4.0](https://fits.gsfc.nasa.gov/standard40/fits_standard40aa-le.pdf).

## Headers

### Keyword Records

| | Status | Requirement |
|:---:|:---|:---|
| :angry: | Not Started | An encoded keyword record shall be exactly 80 characters. |
| :angry: | Not Started | One key shall be present in a keyword record. |
| :angry: | Not Started | Zero or one value shall be present in a keyword record. |
| :angry: | Not Started | Zero or one comment shall be present in a keyword record. |

#### Keys

| | Status | Requirement |
|:---:|:---|:---|
| :angry: | Not Started | A key shall be at least one character. |
| :angry: | Not Started | A key shall not be more than eight characters. |
| :angry: | Not Started | A key shall contain only digits (0-9), upper case letters (A-Z), underscores (\_), or hyphens (-). |
| :angry: | Not Started | A key shall not contain leading 0s in counter suffixes. (`NAXIS001` is illegal; `NAXIS1` is correct.) |
| :angry: | Not Started | An encoded key that is less than eight characters shall fill the remaining characters with spaces. An example is `KEY'''''` (apostrophes are used for spaces here, for visualization). |

#### Values

| | Status | Requirement |
|:---:|:---|:---|
| :angry: | Not Started | An encoded value shall be preceded by `= ` (one equal sign, and one space). |
| :angry: | Not Started | A value shall be one of the following types: string, boolean, integer number, real number, complex integer number, complex real number. |

#### Comments

| | Status | Requirement |
|:---:|:---|:---|
| :angry: | Not Started | A comment which follows a value shall be preceded by a `/` character. |
| :angry: | Not Started | A comment shall contain only ASCII characters 32 - 126 (decimal). |
