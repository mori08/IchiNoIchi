#include <IchiNoIchi/MyLibrary.hpp>

namespace IchiNoIchi
{
	void registerResourceAndAsset()
	{
#ifdef _DEBUG

		TextReader resourceReader(U"Resource.rc");
		Array<String> resourceList;
		while (const auto line = resourceReader.readLine())
		{
			resourceList << line.value();
			if (line == U"// from here") { break; }
		}
		resourceReader.close();

		Array<FilePath> contents = FileSystem::DirectoryContents(U"asset", Recursive::Yes);
		TextWriter listWriter(U"asset/list");
		for (const auto& content : contents)
		{
			if (FileSystem::IsDirectory(content)) { continue; }

			const FilePath filePath = FileSystem::RelativePath(content);
			listWriter.writeln(filePath);
			resourceList << (U"Resource(" + filePath + U")");

			if (FileSystem::Extension(filePath) == U"png")
			{
				TextureAsset::Register(FileSystem::BaseName(content), filePath);
			}

			if (FileSystem::Extension(filePath) == U"mp3")
			{
				AudioAsset::Register(FileSystem::BaseName(content), filePath);
			}
		}
		listWriter.close();

		TextWriter resourceWriter(U"Resource.rc");
		for (const auto& line : resourceList) { resourceWriter.writeln(line); }
		resourceWriter.close();
#else
		TextReader reader(Resource(U"asset/list"));
		while (auto line = reader.readLine())
		{
			String content = line.value();
			String fileName = FileSystem::FileName(content);

			if (FileSystem::Extension(content) == U"png")
			{
				TextureAsset::Register(FileSystem::BaseName(content), Resource(content));
			}

			if (FileSystem::Extension(content) == U"mp3")
			{
				AudioAsset::Register(FileSystem::BaseName(content), Resource(content));
			}
		}
#endif // _DEBUG
	}

	FilePath assetPath(const FilePath& assetPath)
	{
#ifdef _DEBUG
		return U"asset/" + assetPath;
#else
		return Resource(U"asset/" + assetPath);
#endif // _DEBUG
	}

	Array<Point> getGridPoint(const Rect& rect)
	{
		Array<Point> rtn;

		for (int32 x : Range(rect.x, rect.x + rect.w))
		{
			for (int32 y : Range(rect.y, rect.y + rect.h))
			{
				rtn.emplace_back(x, y);
			}
		}

		return std::move(rtn);
	}

	int32 randomFrequency(double frequency)
	{
		return Random(1.0 / Scene::DeltaTime()) < frequency;
	}
}
