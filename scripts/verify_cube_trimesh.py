import os
import trimesh


def get_mesh_file_path(basename):

    current_file_dir = os.path.dirname(__file__)
    meshes_dir = os.path.abspath(os.path.join(current_file_dir, '..', 'meshes'))
    return os.path.join(meshes_dir, basename)


def verify_cube_model():

    fname = get_mesh_file_path('Cube.stl')
    mesh = trimesh.load_mesh(fname)
    assert len(mesh.vertices) == 8
    assert len(mesh.faces) == 12


if __name__ == '__main__':

    verify_cube_model()