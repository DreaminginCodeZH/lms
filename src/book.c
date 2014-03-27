/*
 * File: book.c
 * Author: Zhang Hai
 */

#include "book.h"


static void book_delete(Book *book);


/**
 * Create a new instance of {@link Book}.
 * The constructor will make copies of the strings passed in.
 * The reference count will be set to 1.
 * @param title
 * @param authors
 * @param number
 * @param subjects
 * @param publisher
 * @param year
 * @param circulating
 * @return The created {@link Book} instance.
 */
Book *book_new(char *title, char *authors[5], char *number,
        char *subjects[5], char *publisher, char *year,
        BOOL circulating) {

    Book *book = LMS_NEW(Book);

    book->reference_count = 1;
    book->title = string_clone(title);
    string_array_clone(authors, book->authors, 5);
    book->number = string_clone(number);
    string_array_clone(subjects, book->subjects, 5);
    book->publisher = string_clone(publisher);
    book->year = string_clone(year);
    book->circulating = circulating;

    return book;
}

/**
 * @private
 * Destroy a {@link Book} instance.
 * @param book The {@link Book} instance to be destroyed.
 */
static void book_delete(Book *book) {

    free(book->title);
    string_array_free(book->authors, 5);
    free(book->number);
    string_array_free(book->subjects, 5);
    free(book->publisher);
    free(book->year);

    free(book);
}

/**
 * Add a reference to a {@link Book} instance.
 * @param book The {@link Book} instance to add a reference to.
 */
void book_add_reference(Book *book) {
    ++book->reference_count;
}

/**
 * Remove a reference to a {@link Book} instance, will delete the
 * instance if reference count reaches 0.
 * @param book The {@link Book} instance to remove a reference from.
 */
void book_remove_reference(Book *book) {
    if(--book->reference_count == 0) {
        book_delete(book);
    }
}

/**
 * Serialize a {@link Book} to file.
 * @param book The {@link Book} to be serialized.
 * @param file The file to serialize {@param book}.
 * @return Whether the serialization was successful.
 */
BOOL book_serialize(Book *book, FILE *file) {
    return serialize_string(book->title, file)
            && serialize_string_array(book->authors, 5, file)
            && serialize_string(book->number, file)
            && serialize_string_array(book->subjects, 5, file)
            && serialize_string(book->publisher, file)
            && serialize_string(book->year, file)
            && serialize_bool(&book->circulating, file);
}

/**
 * Deserialize a {@link Book} from file.
 * @param file The file to deserialize a {@link Book} from.
 * @return A {@link Book} deserialized from {@param file}, or NULL if
 *         an error occurred.
 */
Book *book_deserialize(FILE *file) {
    Book *book = LMS_NEW(Book);
    if (deserialize_string(&book->title, file)
            && deserialize_string_array(book->authors, 5, file)
            && deserialize_string(&book->number, file)
            && deserialize_string_array(book->subjects, 5, file)
            && deserialize_string(&book->publisher, file)
            && deserialize_string(&book->year, file)
            && deserialize_bool(&book->circulating, file)) {
        book->reference_count = 1;
        return book;
    } else {
        book_delete(book);
        return NULL;
    }
}

/**
 * @deprecated In most cases you may want to use
 *             {@link book_add_reference} instead.
 * Clone a {@link Book} instance.
 * @param book The {@link Book} instance to clone.
 * @return The cloned {@link Book} instance.
 */
Book *book_clone(Book *book) {
    return book_new(book->title, book->authors, book->number,
            book->subjects, book->publisher, book->year,
            book->circulating);
}

/**
 * Check if two {@link Book} instances are equal.
 * @param book1 The first {@link Book} instance.
 * @param book2 The second {@link Book} instance.
 * @return Whether the two {@link Book} instances are equal.
 */
BOOL book_is_equal(Book *book1, Book *book2) {
    return strcmp(book1->title, book2->title) == 0
            && string_array_is_equal(book1->authors, book2->authors, 5)
            && strcmp(book1->number, book2->number) == 0
            && string_array_is_equal(book1->subjects, book2->subjects, 5)
            && strcmp(book1->publisher, book2->publisher) == 0
            && strcmp(book1->year, book2->year) == 0
            && book1->circulating == book2->circulating;
}

/**
 * Print the information stored in a {@link Book} instance.
 * @param book The {@link Book} instance to print.
 */
void book_print(Book *book) {
    printf("Title:              %s\n", book->title);
    printf("Author(s):          ");
    string_array_print(book->authors, 5);
    printf("\n");
    printf("LoC catalog number: %s\n", book->number);
    printf("Subject(s):         ");
    string_array_print(book->subjects, 5);
    printf("\n");
    printf("Publisher:          %s\n", book->publisher);
    printf("Year:               %s\n", book->year);
    printf("Circulating:        ");
    bool_print(book->circulating);
    printf("\n");
}
