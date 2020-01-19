#ifndef movie_h_
#define movie_h_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <map>

class Movie {
public:
	Movie() : occupied(false) {}

	Movie(const Movie& mo) {
		this -> copy(mo);
	}

	Movie(std::string title_, std::vector<std::string> genres_,
		std::vector<std::string> roles_, std::vector< const 
		std::pair<const std::string, std::string>* > actors_, 
		size_t year_of_release_, size_t run_time_) {

		title = title_;
		genres = genres_;
		roles = roles_;
		actors = actors_;
		year_of_release = year_of_release_;
		run_time = run_time_;
		std::string whole = title + 
		std::to_string(year_of_release) +
		std::to_string(run_time);
		// All components of the string that is hashed. 
		// Each index can potentially be replaced with '?'
		// for a partial hash. 
		hashes = std::vector<std::string>(6); 

		hashes[0] = title;
		hashes[1] = std::to_string(year_of_release);
		hashes[2] = std::to_string(run_time);

		std::string s = "";
		for (int i = 0; i < genres.size(); i++) {
			s += std::to_string(i) + genres[i];
			whole += std::to_string(i) + genres[i];
		}

		hashes[3] = s;

		s = "";
		for (int i = 0; i < actors.size(); i++) {
			s += std::to_string(i) + actors[i] -> first;
			whole += std::to_string(i) + actors[i] -> first;
		}
		

		hashes[4] = s;
		

		s = "";
		for (int i = 0; i < roles.size(); i++) {
			s += std::to_string(i) + roles[i];
			whole += std::to_string(i) + roles[i];
		}

		hashes[5] = s;

		h_movie = movie_hash(whole);
		
		occupied = true;

	}

	void copy(const Movie& mo) {
		title = mo.title;
		genres = mo.genres;
		actors = mo.actors;
		roles = mo.roles;
		year_of_release = mo.year_of_release;
		run_time = mo.run_time;
		h_movie = mo.h_movie;
		occupied = mo.occupied;
		hashes = mo.hashes;
	}

	bool operator==(const Movie& m_) const {
		return title == m_.title && year_of_release
		 == m_.year_of_release && run_time == 
		 m_.run_time && h_movie == m_.h_movie 
		 && genres == m_.genres && roles == 
		 m_.roles && actors == m_.actors;
	}

	bool operator!=(const Movie&m_) const {
		return !((*this) == m_);
	}

	Movie& operator=(const Movie& m) {
		this -> copy(m);

		return *this;
	}

	void print_movie() const {
		std::cout << title << std::endl;
		std::cout << year_of_release << 
		std::endl << run_time << std::endl;

		std::cout << genres.size();
		for (int i = 0; i < genres.size(); i++) {
			std::cout << ' ' << genres[i];
		}
		std::cout << std::endl << actors.size();

		for (int i = 0; i < actors.size(); i++) {
			std::cout << ' ' << actors[i] -> second << " (" << 
			roles[i] << ")";
		}
		std::cout << std::endl;
	}
	


private:

	friend class Table;
	size_t movie_hash(const std::string& key) const {
		//  This implementation comes from 
		//  http://www.partow.net/programming/hashfunctions/
		//
		//  This is a general-purpose, very good hash function for strings.
		size_t hash = 1315423911;
		for(size_t i = 0; i < key.length(); i++) {
			hash ^= ((hash << 5) + (size_t)key[i] + (hash >> 2));
		}
		return hash;
	}

	// size_t movie_hash(const std::string& key) const {
	//     size_t hash = 5381;
		// my own hash function. 
	//     for (int c = 0; c < key.size(); c++) {
	//         hash = ((hash << 5) + hash) + key[c];
	//     }

	//     return hash;
	// }

	//MOVIE REPRESENTATION 
	std::string title;
	std::vector<std::string> genres;
	std::vector<std::string> roles;
	std::vector< const std::pair<const 
		std::string, std::string>* > actors;

	size_t year_of_release;
	size_t run_time;
	size_t h_movie;
	std::vector<std::string> hashes;
	bool occupied;
};



#endif