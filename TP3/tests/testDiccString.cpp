#include "tests.h"

const std::string word_list[] = {"about", "after", "again", "air", "all",
"along", "also", "an", "and", "another", "any", "are", "around", "as", "at",
"away", "back", "be", "because", "been", "before", "below", "between", "both",
"but", "by", "came", "can", "come", "could", "day", "did", "different", "do",
"does", "do't", "down", "each", "end", "even", "every", "few", "find", "first",
"for", "found", "from", "get", "give", "go", "good", "great", "had", "has",
"have", "he", "help", "her", "here", "him", "his", "home", "house", "how",
"I", "if", "in", "into", "is", "it", "its", "just", "know", "large", "last",
"left", "like", "line", "little", "long", "look", "made", "make", "man", "many",
"may", "me", "men", "might", "more", "most", "Mr.", "must", "my", "name",
"never", "new", "next", "no", "not", "now", "number", "of", "off", "old",
"on", "one", "only", "or", "other", "our", "out", "over", "own", "part",
"people", "place", "put", "read", "right", "said", "same", "saw", "say",
"see", "she", "should", "show", "small", "so", "some", "something", "sound",
"still", "such", "take", "tell", "than", "that", "the", "them", "then",
"there", "these", "they", "thing", "think", "this", "those", "thought",
"three", "through", "time", "to", "together", "too", "two", "under", "up",
"us", "use", "very", "want", "water", "way", "we", "well", "went", "were",
"what", "when", "where", "which", "while", "who", "why", "will", "with", "word",
"work", "world", "would", "write", "year", "you", "your", "was"};

void test_definir_obtener() {
    DiccString<int> dictest = DiccString<int>();

    for (int i = 0; i < 187; ++i) {
        dictest.Definir(word_list[i], i);
        ASSERT(dictest.Definido(word_list[i]));
        ASSERT_EQ(dictest.Obtener(word_list[i]), i);
    }
}

void test_definir_obtener_string() {
    DiccString<std::string> dic_test_string = DiccString<std::string>();

    for (int i = 0; i < 187; ++i) {
        dic_test_string.Definir(word_list[i], word_list[i]);
        ASSERT(dic_test_string.Definido(word_list[i]));
        ASSERT_EQ(dic_test_string.Obtener(word_list[i]), word_list[i]);
    }
}

void test_definir_obtener_dicc_string() {
    DiccString<DiccString<int> > compuesto = DiccString<DiccString<int> >();

    for (int i = 0; i < 187; ++i){
        compuesto.Definir(word_list[i], DiccString<int>());
        compuesto.Obtener(word_list[i]).Definir(word_list[i], i);

        ASSERT_EQ(compuesto.Obtener(word_list[i]).Obtener(word_list[i]), i);
    }
}

void test_dicc_string() {
    RUN_TEST(test_definir_obtener);
    RUN_TEST(test_definir_obtener_string);
    RUN_TEST(test_definir_obtener_dicc_string);
}
