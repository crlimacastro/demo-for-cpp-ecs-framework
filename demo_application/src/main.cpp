#include "fae_framework.hpp"

using namespace fae;

entity spawn_light(fae::application_step& step, int type, const raylib::Vector3& position, const raylib::Vector3& target, const raylib::Color& color)
{
	auto entity = step.create_entity();
	step.get_resource<common_resources>().match([&](common_resources& common_resources)
		{
			entity.set_component<Light>(CreateLight(type, position, target, color, common_resources.lighting_shader));
		}, []() {
		});
	return entity;
}

entity spawn_cube(fae::application_step& step, const raylib::Vector3& translation = { 0, 0, 0 }, const raylib::Quaternion& rotation = { 0, 0, 0, 1 }, const raylib::Vector3& scale = { 1, 1, 1 }, const raylib::Color& color = raylib::Color::White(), reactphysics3d::BodyType body_type = reactphysics3d::BodyType::DYNAMIC)
{
	auto entity = step.create_entity();
	entity
		.set_component<raylib::Transform>(translation, rotation, scale)
		.set_component<raylib::Color>(color)
		.set_component<visibility>(true)
		;


	step.get_resource<common_resources>().match([&](common_resources& common_resources)
		{
			entity
				.set_component<raylib::Model>(raylib::Model(raylib::Mesh::Cube(1, 1, 1)))
				.get_component<raylib::Model>().match([&](raylib::Model& model)
					{
						model.materials[0].shader = common_resources.lighting_shader;
					}, []() {});
		}, []() {
		});
	step.get_resource<physics>().match([&](physics& physics)
		{
			auto rigid_body = physics.world->createRigidBody(reactphysics3d::Transform({ translation.x, translation.y, translation.z }, reactphysics3d::Quaternion{ rotation.x, rotation.y, rotation.z, rotation.w }));
			rigid_body->addCollider(physics.common.createBoxShape({ .5f * scale.x, .5f * scale.y, .5f * scale.z }), reactphysics3d::Transform::identity());
			rigid_body->updateMassPropertiesFromColliders();
			rigid_body->setType(body_type);
			entity.set_component<fae::rigid_body>(rigid_body);
		}, []() {});
	return entity;
}

void start(start_step& step)
{
	step.get_resource<clear_color>().match([](clear_color& clear_color) {
		clear_color.color = raylib::Color::SkyBlue();
		}, []() {});
	step.get_resource<active_camera_3d>().match([](active_camera_3d& active_camera_3d) {
		active_camera_3d.camera_entity.match([](entity& camera_entity) {
			camera_entity.get_component<raylib::Transform3>().match([](raylib::Transform3& transform) {
				transform.SetTranslation(raylib::Vector3(8, 10, 8));
				transform.SetRotation(raylib::Quaternion::FromEuler(to_radians(45), to_radians(180 + 45), to_radians(0)));
				}, []() {});
			}, []() {});
		}, []() {});
	spawn_light(step, LIGHT_DIRECTIONAL, { 0, 0, 0 }, { 1, -1, 0 }, raylib::Color::White());
	for (size_t i = 0; i < 256; i++)
	{
		float scale = random_range(0.1, 0.5);
		spawn_cube(step, raylib::Vector3(random_range(-4, 4), 16, random_range(-4, 4)), raylib::Quaternion::FromEuler(to_radians(random_range(0, 360)), to_radians(random_range(0, 360)), to_radians(random_range(0, 360))), raylib::Vector3(scale, scale, scale), raylib::Color::FromHSV(random_range(0, 360), random_range(0, 1), random_range(0, 1)), reactphysics3d::BodyType::DYNAMIC);
	}
	spawn_cube(step, raylib::Vector3(0, 0, 0), raylib::Quaternion::Identity(), raylib::Vector3(10, 0.05f, 10), raylib::Color::RayWhite(), reactphysics3d::BodyType::STATIC);
}

void update(update_step& step)
{
}

void draw(draw_step& step)
{
	DrawFPS(4, 4);
}

int main()
{
	application{}
		.add_plugin<&default_plugins>()
		.set_system<start_step, &start>()
		.set_system<update_step, &quit_on_esc>()
		.set_system<update_step, &update>()
		.set_system<draw_step, &draw>()
		.run();
}