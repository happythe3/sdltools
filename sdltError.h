/*
Copyright 2018 Alexander Shearer

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once


#include <string>


namespace qdt {
	struct error {
		// Source of error
		std::string source;
		std::string msg;
	};

		struct resource_error : error {
			resource_error(std::string s, std::string p, std::string m) {
				source = s;
				path = p;
				msg = m;
			}
			std::string path;
		};

			struct already_loaded : resource_error {
				already_loaded(std::string s, std::string p, std::string m)
					:resource_error(s, p, m) {}
			};

			struct not_loaded : resource_error {
				not_loaded(std::string s, std::string p, std::string m)
					:resource_error(s, p, m) {}
			};

			struct NULL_error : resource_error {
				NULL_error(std::string s, std::string p, std::string m)
					:resource_error(s, p, m) {}
			};

				struct NULL_surface : NULL_error {
					NULL_surface(std::string s, std::string p, std::string m)
						:NULL_error(s, p, m) {}
				};

				struct NULL_texture : NULL_error {
					NULL_texture(std::string s, std::string p, std::string m)
						:NULL_error(s, p, m) {}
				};

		struct render_error : error {
			render_error(std::string s, std::string m) {
				source = s;
				msg = m;
			}
		};

		struct node_error : error {
			node_error(std::string s, std::string m) {
				source = s;
				msg = m;
			}
		};
}