#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <map>
#include <list>

#include "table.h"

void parse_actors(std::map<std::string, 
	std::string>& nconsts, std::ifstream& f_actors); 

void parse_movies(Table& data, std::ifstream& f_movies, 
	const std::map<std::string, std::string>& nconsts, 
	std::list<Movie>& all_movies, Movie& m);

int main() {
	bool actors_open = false;
	bool movies_open = false;
	std::string parse;
	size_t N = 100;
	float f = 0.5;
	std::ifstream f_movies;
	std::ifstream f_actors;

	Table data(N, f);

	std::map<std::string, std::string> nconsts;

	std::list<Movie> all_movies;
	Movie m;
	while(1) {
		std::cin >> parse;
		if (parse == std::string("quit")) {
			return 0;
		}

		if (parse == std::string("movies") || 
			parse == std::string("actors")) {

			if (parse == std::string("movies")) {
				std::cin >> parse;
				f_movies.open(parse);
				assert(f_movies.good());
				movies_open = true;
			}

			if (parse == std::string("actors")) {
				std::cin >> parse;
				f_actors.open(parse);
				assert(f_actors.good());
				actors_open = true;
			}

			if (movies_open && actors_open) {
				parse_actors(nconsts, f_actors);
				parse_movies(data, f_movies, nconsts, 
					all_movies, m);
				// data.print_table();
				// all_movies.back().print_movie();

			}
		}

		if (parse == std::string("table_size")) {
			std::cin >> N;
			data = Table(N, f);
		}

		if (parse == std::string("occupancy")) {
			std::cin >> f;

			data = Table(N, f);
		}

		if (parse == std::string("query")) {
			
			// data.print_table();

			std::vector<std::string> query(6);
			std::string s;
			size_t k = 0;
			std::cin >> query[0];
			std::cin >> query[1];
			std::cin >> query[2];

			std::cin >> k;

			if (k == 0) {
				query[3] = "?";
			} else {
				for (int i = 0; i < k; i++) {
					std::cin >> s;
					query[3] += std::to_string(i) + s;
				}
			}

			std::cin >> k;
			if (k == 0) {
				query[4] = "?";
			} else {
				for (int i = 0; i < k; i++) {
					std::cin >> s;
					query[4] += std::to_string(i) + s;
				}
			}

			std::cin >> k;
			if (k == 0) {
				query[5] = "?";
			} else {
				for (int i = 0; i < k; i++) {
					std::cin >> s;
					query[5] += std::to_string(i) + s;
				}
			}

			s = "";
			for (int i = 0; i < query.size(); i++) { /*DS_IV:Submitty_Strikes_Back?????*/
				s += query[i];
			}

			// std::cout << "GOODMORNINGRPI" << std::endl;
			// std::cout << s;
			
			std::list<Movie*> result = data.query(s);
			if (result.size() == 0) {
				std::cout << "No results for query." << std::endl;
			} else {
				std::cout << "Printing " << result.size()
				 << " result(s):" << std::endl;

				for (std::list<Movie*>::const_iterator i = result.begin(); i != result.end(); i++) {
					(*i) -> print_movie();
				}
			}

			// data.print_table();
		}
	}
}

void parse_actors(std::map<std::string, 
	std::string>& nconsts, std::ifstream& f_actors) {
	std::string key;
	while (f_actors >> key) {
		f_actors >> nconsts[key];
	}
}

void parse_movies(Table& data, std::ifstream& f_movies, 
	const std::map<std::string, std::string>& nconsts, 
	std::list<Movie>& all_movies, Movie& m) {

	std::string title;
	
	size_t year_of_release;
	size_t run_time;
	size_t k;
	std::string s;


	while(f_movies >> title) {

		std::vector<std::string> genres;
		std::vector<std::string> roles;
		std::vector <const std::pair<const std::string, 
		std::string>* > actors;

		f_movies >> year_of_release;
		f_movies >> run_time;
		f_movies >> k;

		for (int i = 0; i < k; i++) {
			f_movies >> s;
			genres.push_back(s);
		}

		// nm6127437 DonaldTrump
		f_movies >> k;
		for (int i = 0; i < k; i++) {
			f_movies >> s;
			std::map<std::string, std::string>::const_iterator 
			a_iter = nconsts.find(s);

			assert(a_iter != nconsts.end());
			actors.push_back(&(*nconsts.find(s)));
		}

		f_movies >> k;
		for (int i = 0; i < k; i++) {
			f_movies >> s;
			roles.push_back(s);
		}

		// std::cout << title << std::endl;
		m = Movie(title, genres, roles, actors, 
			year_of_release, run_time);
		all_movies.push_back(m);

		data.insert(&(all_movies.back()));
	}

	// std::cout << all_movies.size() << std::endl;

	// std::cout << data.size() << std::endl;
}