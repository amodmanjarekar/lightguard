#[derive(Debug)]
#[repr(C)]
pub struct Vector2 {
    x: f32,
    y: f32,
}

#[repr(C)]
pub struct PassData {
    points_array: [Vector2; 7],
}

#[no_mangle]
pub extern "C" fn perform(d: *mut PassData) {
    unsafe {
        (*d).points_array.iter().for_each(|x| println!("{:?}", x));
    }
}
