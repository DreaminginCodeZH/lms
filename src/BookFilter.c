/*
 * File: BookFilter.c
 * Author: Zhang Hai
 */

#include "BookFilter.h"

#include "Library/ArrayList.h"


#define DEFINE_BOOK_FILTER_STRING(member) \
    bool BookFilters_##member(Book *book, void *member) { \
        return string_contains(book->member, member); \
    }

#define DEFINE_BOOK_FILTER_STRING_ARRAY(member, size) \
    bool BookFilters_##member(Book *book, void *member) { \
        return string_array_contains(book->member, size, member); \
    }

#define DEFINE_BOOK_FILTER_BOOL(member) \
    bool BookFilters_##member(Book *book, void *member) { \
        return bool_is_equal(book->member, member); \
    }


BookFilterFunction BOOK_FILTERS[] = {
    BookFilters_string,
    BookFilters_title,
    BookFilters_authors,
    BookFilters_number,
    BookFilters_publisher,
    BookFilters_subjects,
    BookFilters_year,
    BookFilters_circulating,
};

size_t BOOK_FILTERS_SIZE = 8;


DEFINE_BOOK_FILTER_STRING(title)

DEFINE_BOOK_FILTER_STRING_ARRAY(authors, 5)

DEFINE_BOOK_FILTER_STRING(number)

DEFINE_BOOK_FILTER_STRING_ARRAY(subjects, 5)

DEFINE_BOOK_FILTER_STRING(publisher)

DEFINE_BOOK_FILTER_STRING(year)

DEFINE_BOOK_FILTER_BOOL(circulating)

bool BookFilters_string(Book *book, void *theString) {
    return BookFilters_title(book, theString)
            || BookFilters_authors(book, theString)
            || BookFilters_number(book, theString)
            || BookFilters_subjects(book, theString)
            || BookFilters_publisher(book, theString)
            || BookFilters_year(book, theString);
}

bool BookFilters_compound(Book *book, void *list) {
    ArrayList *filters = list;
    BookFilter *filter;
    ARRAY_LIST_FOR_EACH(filters, filter) {
        if (!filter->filter(filter->filterData)) {
            return false;
        }
    }
    return true;
}


#undef DEFINE_BOOK_FILTER_STRING
#undef DEFINE_BOOK_FILTER_STRING_ARRAY
#undef DEFINE_BOOK_FILTER_BOOL
