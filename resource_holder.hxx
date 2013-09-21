#ifndef AIRWAR_RESOURCE_HOLDER_HXX_INCLUDED
#define AIRWAR_RESOURCE_HOLDER_HXX_INCLUDED

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace airwar
{
	template<typename Resource, typename Identifier>
	class ResourceHolder
	{
	public:
		void load(Identifier id, const std::string &filename);

		template<typename Parameter>
		void load(Identifier id, const std::string &filename, const Parameter &secondParam);

		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;

	private:
		std::map<Identifier, std::unique_ptr<Resource>> resources_;
	};

	template<typename Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename)
	{
		std::unique_ptr<Resource> resource(new Resource);
		if (!resource->loadFromFile(filename))
		{
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}
		auto inserted = resources_.insert({ id, std::move(resource) });
		assert(inserted.second);
	}

	template<typename Resource, typename Identifier>
	template<typename Parameter>
	void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter &secondParam)
	{
		std::unique_ptr<Resource> resource(new Resource);
		if (!resource->loadFromFile(filename, secondParam))
		{
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}
		auto inserted = resources_.insert({ id, std::move(resource) });
		assert(inserted.second);
	}

	template<typename Resource, typename Identifier>
	Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
	{
		auto found = resources_.find(id);
		assert(found != resources_.end());
		return *(found->second);
	}

	template<typename Resource, typename Identifier>
	const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
	{
		auto found = resources_.find(id);
		assert(found != resources_.end());
		return *(found->second);
	}
}

#endif // AIRWAR_RESOURCE_HOLDER_HXX_INCLUDED