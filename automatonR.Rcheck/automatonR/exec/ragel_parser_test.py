import unittest
import ragel_parser

class CheckInputTest(unittest.TestCase):
    def test_check_input_bracket(self):
        self.assertRaises(ValueError, ragel_parser.check_input, "<0.1")

    def test_check_input_at_least_one_alphabet(self):
        self.assertRaises(ValueError, ragel_parser.check_input, "<>+")

    def test_check_input_minimum_alphabet(self):
        self.assertRaises(ValueError, ragel_parser.check_input, "<1>")

    def test_check_input_alphabet_incremental(self):
        self.assertRaises(ValueError, ragel_parser.check_input, "<0.2>")

    def test_check_input_non_integer_alphabet(self):
        self.assertRaises(ValueError, ragel_parser.check_input, "<a.b>")

    def test_global_alphabet_count(self):
        ragel_parser.check_input("<0.1.2>")
        self.assertEqual(ragel_parser.global_alphabet_counter, 3)

        ragel_parser.check_input("<0.1.0>")
        self.assertEqual(ragel_parser.global_alphabet_counter, 2)


class ParserTest(unittest.TestCase):
    def test_clock_counter(self):
        ragel_parser.global_clock_counter = 0
        ragel_parser.parser("<0>")
        self.assertEqual(ragel_parser.global_clock_counter, 1)
        ragel_parser.global_clock_counter = 0
        ragel_parser.parser("<0>.<1>")
        self.assertEqual(ragel_parser.global_clock_counter, 2)
        ragel_parser.global_clock_counter = 0
        ragel_parser.parser("<0>.<1>.<2>")
        self.assertEqual(ragel_parser.global_clock_counter, 3)

    def test_one_element_plus_inside(self):
        ragel_parser.global_clock_counter = 0
        self.assertEqual("((0+) @CT0 >~ST0) @U $~STEP $lerr(R);", ragel_parser.parser("<0+>"))

    def test_one_element_plus_outside(self):
        ragel_parser.global_clock_counter = 0
        self.assertEqual("(((0) @CT0 >~ST0)+) @U $~STEP $lerr(R);", ragel_parser.parser("(<0>)+"))

    def test_non_tre_concat_with_tre(self):
        ragel_parser.global_clock_counter = 0
        self.assertEqual("(1.(0+)) @U $~STEP $lerr(R);", ragel_parser.parser("1.(0+)"))

    def test_one_regular_tre(self):
        ragel_parser.global_clock_counter = 0
        self.assertEqual("((0.1) @CT0 >~ST0) @U $~STEP $lerr(R);", ragel_parser.parser("<0.1>"))

    def test_tre_concatenation(self):
        ragel_parser.global_clock_counter = 0
        self.assertEqual("((0) @CT0 >~ST0.(1) @CT1 >~ST1.(2) @CT2 >~ST2) @U $~STEP $lerr(R);", ragel_parser.parser("<0>.<1>.<2>"))

    def test_nested_tre(self):
        ragel_parser.global_clock_counter = 0
        self.assertEqual("((0.(1.2) @CT1 >~ST1) @CT0 >~ST0) @U $~STEP $lerr(R);", ragel_parser.parser("<0.<1.2>>"))

    def test_union(self):
        ragel_parser.global_clock_counter = 0
        self.assertEqual("(0.((1.2) @CT0 >~ST0 | (3) @CT1 >~ST1) @U $~STEP $lerr(R);", ragel_parser.parser("0.(<1.2> | <3>"))


if __name__ == '__main__':
    unittest.main()





