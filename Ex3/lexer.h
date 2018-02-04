#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "token.h"
#include <functional>

namespace parser
{
	class token;
	enum class token_kind;

	class lexer
	{
		typedef std::function <bool  ( lexer& )> predicate;

	public:
		explicit lexer ( std::string );

		/**
		 * \brief Advances the lexer once.
		 */
		void advance ();

		/**
		 * \brief Advances the lexer until the NULL terminator character is reached.
		 */
		void advance_until_end ();

		/**
		 * \brief Advances the lexer while the specified predicate function returns true.
		 */
		void advance_while ( predicate );

		/**
		 * \brief Advances the lexer until the specified predicate function returns true.
		 */
		void advance_until ( predicate );

		/**
		 * \brief Advances the lexer while the specified predicate function returns true.
		 * \return The characters that were captured in the process.
		 */
		void advance_while ( predicate, std::vector <char>& );

		/**
		 * \brief Advances the lexer until the specified predicate function returns true.
		 * \return The characters that were captured in the process.
		 */
		void advance_until ( predicate, std::vector <char>& );

		/**
		 * \brief Advances the lexer, but does not capture any characters.
		 */
		void eat ();

		/**
		 * \brief 
		 * \return The current position.
		 */
		uint16_t get_position () const;

		/**
		 * \brief 
		 * \return The current column.
		 */
		uint16_t get_column () const;

		/**
		 * \brief 
		 * \return The current line.
		 */
		uint16_t get_line () const;

		/**
		 * \brief 
		 * \return A pointer to the current character.
		 */
		const char* current_ptr () const;

		/**
		 * \brief 
		 * \return The current character.
		 */
		char current () const;

		/**
		 * \brief 
		 * \return The next character.
		 */
		char next () const;

		/**
		 * \brief 
		 * \return The previous character.
		 */
		char previous () const;

		/**
		 * \brief 
		 * \return A collection of tokens that have been parsed.
		 */
		std::vector <token> tokens () const;

	private:
		void tokenize ();

		void parse_alpha ();
		void parse_numeric ();

		void refresh ();

		std::string m_str;
		const char* m_ptr { };

		char m_current { }, m_next { }, m_prev { };

		uint16_t m_position = 1;
		uint16_t m_column   = 1;
		uint16_t m_line     = 1;

		uint16_t m_lastStart { }, m_lastEnd { };

		token_kind m_lastKind;
		std::string m_lastData;

		std::vector <token> m_tokens { };
	};
}
