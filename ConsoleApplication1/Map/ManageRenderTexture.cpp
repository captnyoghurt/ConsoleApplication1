#include "ManageRenderTexture.h"



ManageRenderTexture::ManageRenderTexture()
{
	m_initialized = false;
}


ManageRenderTexture::~ManageRenderTexture()
{
}


// Return if the render texture need to be updated
bool ManageRenderTexture::getUpdated() const
{
	return m_updated;
}


// Return if the render texture is initialized
bool ManageRenderTexture::getInitialized() const
{
	return m_initialized;
}


// Return the render texture surface
std::list<std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator ManageRenderTexture::getRenderTextureSurface()
{
	return m_renderTextureSurface;
}


// Return the vector of all the surfaces on the render texture
std::vector<std::list<std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator> ManageRenderTexture::getSurfaces() const
{
	return m_surfaces;
}
std::list<std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator ManageRenderTexture::getTheSurface(int n)
{
	if ((unsigned)n < m_surfaces.size())
		return m_surfaces.at(n);

	/// Error
	return m_renderTextureSurface;
}


// Return the RenderTexture where all the surfaces are printed with modifying possibilities
sf::RenderTexture& ManageRenderTexture::getRealRenderTexture(bool updateIt)
{
	m_updated = m_updated || updateIt;

	return m_renderTexture;
}


// Return the render texture surface with modifying possibilities
std::list<std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator& ManageRenderTexture::getRealRenderTextureSurface(bool updateIt)
{
	m_updated = m_updated || updateIt;

	return m_renderTextureSurface;
}


// Return the vector of all the surfaces on the render texture with modifying possibilities
std::vector<std::list<std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator>& ManageRenderTexture::getRealSurfaces(bool updateIt)
{
	m_updated = m_updated || updateIt;

	return m_surfaces;
}


// Tell the object to be updated
int ManageRenderTexture::gotUpdated()
{
	m_updated = true;

	return 0;
}


// Add a surface to the render texture
int ManageRenderTexture::add(std::list<std::pair<ManageSurfaces::e_thing, std::shared_ptr<Surface>>>::iterator it, int x, int y)
{
	it->second->setEnable(false);
	

	if (x == -1 && y == -1)
	{
		x = it->second->getX() - m_renderTextureSurface->second->getX();
		y = it->second->getY() - m_renderTextureSurface->second->getY();
	}

	if(it->first == ManageSurfaces::e_thing::SPRITE)
		std::dynamic_pointer_cast<SurfaceSprite>(it->second)->setPosition(float(x), float(y));
	else if (it->first == ManageSurfaces::e_thing::TEXT)
		std::dynamic_pointer_cast<SurfaceText>(it->second)->setPosition(float(x), float(y));

	m_surfaces.push_back(it);

	return 0;
}


// Initialize the render texture
int ManageRenderTexture::load(ManageSurfaces& surf, int x, int y, int w, int h, bool depthBuffer)
{
	m_initialized = true;

	m_renderTexture.create(w, h, depthBuffer);
	m_renderTextureSurface = surf.addSurface(ManageSurfaces::e_thing::SPRITE, std::shared_ptr<Surface>(new SurfaceSprite));
	std::dynamic_pointer_cast<SurfaceSprite>(m_renderTextureSurface->second)->setTexture(m_renderTexture.getTexture());
	m_renderTextureSurface->second->setDimensions(x, y, w, h);

	return 0;
}


// Update the render texture if necessary
int ManageRenderTexture::update()
{
	if (!m_initialized)
		return -1;
	if (!m_updated)
		return 1;

	// Back to a non updated render texture
	m_updated = false;

	
	// Clear the texture
	m_renderTexture.clear(sf::Color(0, 0, 0, 0));

	// Draw every texture
	for (unsigned int i(0); i < m_surfaces.size(); ++i)
	{
		if (m_surfaces.at(i)->first == ManageSurfaces::e_thing::SPRITE)
			m_renderTexture.draw(*std::dynamic_pointer_cast<SurfaceSprite>(m_surfaces.at(i)->second));
		else if (m_surfaces.at(i)->first == ManageSurfaces::e_thing::TEXT)
			m_renderTexture.draw(*std::dynamic_pointer_cast<SurfaceText>(m_surfaces.at(i)->second));
	}

	m_renderTexture.display();

	// Render it to the real screen
	std::dynamic_pointer_cast<SurfaceSprite>(m_renderTextureSurface->second)->setTexture(m_renderTexture.getTexture());

	return 0;
}